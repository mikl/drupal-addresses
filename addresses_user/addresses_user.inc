<?php
// $Id$
/**
 * @author Bruno Massa
 * @file
 * You can associate a geographic address with users.
 */

/**
 * Delete a given Address
 *
 * @param $id
 *   Number. The Address ID that should be deleted
 * @param $type
 *   String (optional). It can be:
 *   - 'address' (default): than search for a unique Address ID
 *   - 'user': get all address from a user
 *   - 'node: get all address from a node
 */
function _addresses_user_address_delete($id, $type = 'address') {
  // Check what address should be deleted: a single one or
  // all addresses related to a given Element (Node, User)
  if ($type == 'address') {
    db_query('DELETE FROM {addresses} WHERE aid = %d', $id);
  }
  else {
    db_query("DELETE FROM {addresses} WHERE aid = %d AND atype = '%s'", $id, $type);
  }

  // Show an warning message
  drupal_set_message(t('The address has been deleted.'), 'warning');
}

/**
 * Load the full address from a given Address ID or User ID
 *
 * @param $id
 *   Number. The ID to look into the table. Depends on $type variable:
 *   if it is 'address' (default), it should look for a unique address
 *   ID, on 'aid' column. For anything else, search on 'eid' column.
 * @param $type
 *   String (optional). It can be:
 *   - 'address' (default): than search for a unique Address ID
 *   - 'user': get all address from a user
 *   - 'node: get all address from a node
 * @return
 *   Array. The numeric list of addresses arrays
 */
function _addresses_user_address_get($id, $type = 'address') {
  static $addresses;

  if (empty($addresses[$type][$id])) {
    // Get the address based on Address ID or
    // the (User/Node) ID and the given identification
    if ($type == 'address') {
      $adr = db_query('SELECT * FROM {addresses} WHERE aid = %d', $id);
    }
    else {
      $adr = db_query("SELECT * FROM {addresses}
        WHERE atype = '%s' AND eid = %d
        ORDER BY is_primary DESC", $type, $id);
    }

    // Transform all SQL findings into arrays
    $addresses[$type][$id] = array();
    while ($address = db_fetch_array($adr)) {
      $addresses[$type][$id][] = $address;
    }
  }

  return $addresses[$type][$id];
}

/**
 * Saves a address and link it to its main object.
 * Needs a $user or $node object.
 *
 * @param $address
 *   Array. The address data to be saved.
 * @param $id
 *   Number. It might be the Node ID (nid) or the User ID (uid),
 *   depending on the $type variable
 * @param $type
 *   String (optional). 'node' to link the address to a
 *   node or 'user' to link it to a site user
 */
function _addresses_user_address_save($address, $id, $type = 'node') {
  if (!empty($address)) {
    if (empty($address['aid'])) {
      $aid_sql = '';
      $aid_sql2 = '';
    }
    else {
      // Instead of create INSERT and UPDATE SQL
      // instrauctions, we DELETE (if exists) the given
      // Address and create another one in its place
      db_query('DELETE FROM {addresses} WHERE aid = %d', $address['aid']);
      $aid_sql = ', aid';
      $aid_sql2 = ', %d';
    }

    // If this address is the Primary, change all other address
    // to NOT primary
    if (!empty($address['is_primary'])) {
      db_query("UPDATE {addresses} SET is_primary = 0
        WHERE is_primary = 1 AND eid = %d AND atype = '%s'",
        $id, $type);
    }

    // Let other modules change the standard behaviour
    module_invoke_all('addressapi', 'save', $address);

    db_query("INSERT INTO {addresses}
      (atype, eid, aname, street,
      additional, city, province, postal_code, country, is_primary". $aid_sql .")
      VALUES ('%s', %d, '%s', '%s',
      '%s', '%s', '%s', '%s', '%s', %d". $aid_sql2 .")",
      $type,
      $id,
      (empty($address['aname'])        ? '' : $address['aname']),
      (empty($address['street'])       ? '' : $address['street']),
      (empty($address['additional'])   ? '' : $address['additional']),
      (empty($address['city'])         ? '' : $address['city']),
      (empty($address['province'])     ? '' : drupal_strtoupper($address['province'])),
      (empty($address['postal_code'])  ? '' : $address['postal_code']),
      (empty($address['country'])      ? '' : $address['country']),
      (empty($address['is_primary'])   ? 0  : $address['is_primary']),
      (empty($address['aid'])          ? 0  : $address['aid'])
    );
  }
}

/**
 * Manage the user Addresses: list them, create and delete operaions
 *
 * @param $op
 *   String (optional). The action that should be executed:
 *   - NULL (default) => list all user addresses
 *   - 'add'          => Address form to add a new address
 *   - 'edit'         => Address form to modify an existing address
 *   - 'delete'       => It will promptly delete the address
 * @param aid
 *   Number (optional). The Address ID
 */
function _addresses_user_address($op = NULL, $aid = NULL) {
  global $user;
  $uid = $user->uid;

  // If the user has the permission to administer
  // other users, he can see others address pages too
  $access = user_access('administer users');
  if (!empty($access)) {
    $uid = arg(1);
  }

  switch ($op) {
    case 'add':
    case 'edit':
      // Its time to include the address form!

      // If its a existing address, get the whole
      // address information
      $edit = arg(4) ? _addresses_user_address_get(arg(4), 'address') : array();

      if (empty($edit)) {
        // Set the Element ID as User ID form new addresses
        $edit[0]['eid'] = $uid;
      }
      elseif (empty($access) or $edit[0]['eid'] != $uid) {
        // If the user has no permission or the user from
        // address is not the same as the user that are
        // accessing, deny the access
        return drupal_access_denied();
      }

      return drupal_get_form('_addresses_user_form', array(), $edit[0]);

    case 'delete':
      /// @todo Generates a confirm page before delete
      _addresses_user_address_delete(arg(4));

      // Send the user to the address book
      drupal_goto("user/$uid/address");
      break;

    default:
      $addresses = _addresses_user_address_get($user->uid, 'user');
      return theme('addresses_user_overview', $uid, $addresses);
  }
}

/**
 * Create a address form for users
 */
function _addresses_user_form(&$form_state, $fields = array(), $values = array()) {
  $form = array();

  // Get the fields used on this address
  $fields = variable_get('addresses_user', array());

  // If its the very first time its loaded, use all fields
  if (empty($fields)) {
    module_load_include('settings.inc', 'addresses');
    $settings = _addresses_settings_fields();
    foreach (array_keys($settings['addresses']) as $index) {
      $fields[$index] = ADDRESSES_FIELD_SHOW;
    }
  }

  // Get the address form builder
  $form['addresses'] = array(
    '#default_value'  => $values,
    '#fields'         => $fields,
    '#required'       => TRUE,
    '#type'           => 'addresses_elements',
    '#tree'           => TRUE
  );

  // Add the submit button
  if (empty($values['aid'])) {
    $form['submit'] = array(
      '#type'   => 'submit',
      '#value'  => t('Create new address')
    );
  }
  else {
    $form['submit'] = array(
      '#type'   => 'submit',
      '#value'  => t('Update address')
    );
  }

  return $form;
}

/**
 * Submit the address
 *
 * @ingroup form
 */
function _addresses_user_form_submit($form, &$form_state) {
  global $user;
  _addresses_user_address_save($form_state['values']['addresses'], $user->uid, 'user');
}

/**
 * List all addresses from a given user
 *
 * @ingroup themeable
 * @param $uid
 *   Number. The user ID
 * @param &$addresses
 *   Array. A list of user addresses
 */
function theme_addresses_user_overview($uid, &$addresses) {
  // Get the current page URL, to force the forms
  // to return here.
  $destination = drupal_get_destination();

  // The option to add a new address is always visible
  $output = "<p>". l(t('Click here to add a new address'),
    "user/$uid/address/add", array('query' => $destination)) .'.</p>';

  // Create a table showing the addresses
  if (!empty($addresses)) {

    // Add each address
    foreach ($addresses as $address) {
      $colunm = array();

      // Display a single address
      $colunm[] = theme('addresses', $address);

      // More readable variable
      $aid = $address['aid'];

      // Add the Edit and Delete options
      $colunm[] = l(t('edit'),
      "user/$uid/address/edit/$aid", array('query' => $destination)) .' / '. l(t('delete'),
      "user/$uid/address/delete/$aid");

      // Each line has two colunms
      $rows[] = $colunm;
    }

    // Create the addresses table
    $header = array(t('address'), t('options'));
    $output .= theme('table', $header, $rows);
  }

  // Show the resulting output
  return $output;
}
