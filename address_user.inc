<?php
/**
 * $Id$
 * @author Bruno Massa
 * @file address_user.inc
 * You can associate a geographic address with users.
 */

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
function _address_user_address($op = NULL, $aid = NULL) {
  include_once ADDRESS_PATH .'/address.inc';

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
      $edit = arg(4) ? _address_address_get(arg(4), 'address') : array();
      $edit = $edit[0];

      if (empty($edit)) {
        // Set the Element ID as User ID form new addresses
        $edit['eid'] = $uid;
      }
      elseif (empty($access) or $edit['eid'] != $uid) {
        // If the user has no permission or the user from
        // address is not the same as the user that are
        // accessing, deny the access
        return drupal_access_denied();
      }

      return drupal_get_form('_address_user_form', array(), $edit);

    case 'delete':
      /// @todo Generates a confirm page before delete
      _address_address_delete(arg(4));

      // Send the user to the address book
      drupal_goto("user/$uid/address");
      break;

    default:
      $addresses = _address_address_get($user->uid, 'user');
      return theme('address_user_overview', $uid, $addresses);
  }
}

/**
 * Create a address form for users
 */
function _address_user_form(&$form_state, $fields = array(), $values = array()) {
  $form = array();

  // Get the address form builder
  _address_form($form, 'user', $values);

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
 */
function _address_user_form_submit($form, &$form_state) {
  global $user;
  _address_address_save($form_state['values']['address'][0], $user, 'user');
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
function theme_address_user_overview($uid, &$addresses) {
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
      $colunm[] = theme('address', $address);

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
