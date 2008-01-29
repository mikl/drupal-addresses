<?php
/**
 * $Id$
 * @author Bruno Massa
 * @file address.inc
 * An implementation of a universal API for address manipulation.
 */

/**
 * Modules settings page
 */
function _address_admin() {
  $form = array();

  $form['location_default_country'] = array(
    '#type'           => 'select',
    '#title'          => t('Default country selection'),
    '#default_value'  => variable_get('address_default_country', 'us'),
    '#options'        => $iso_list_sorted,
    '#description'    => t('This will be the country that is automatically selected when a location form is served for a new location.')
  );

  return $form;
}

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
function _address_address_delete($id, $type = 'address') {
  // Check what address should be deleted: a single one or
  // all addresses related to a given Element (Node, User)
  if ($type == 'address') {
    db_query('DELETE FROM {address} WHERE aid = %d', $id);
  }
  else {
    db_query("DELETE FROM {address} WHERE aid = %d AND atype = '%s'", $id, $type);
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
function _address_address_get($id, $type = 'address') {
  static $addresses;

  if (empty($addresses[$type][$id])) {
    // Get the address based on Address ID or
    // the (User/Node) ID and the given identification
    if ($type == 'address') {
      $adr = db_query('SELECT * FROM {address} WHERE aid = %d', $id);
    }
    else {
      $adr = db_query("SELECT * FROM {address}
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
 * @param &$object
 *   Object. It might be or the $user object or the $node.
 *   We will extract its ID to correct link it to the
 *   address
 * @param $type
 *   String (optional). 'node' to link the address to a
 *   node or 'user' to link it to a site user
 */
function _address_address_save($address, &$object, $type = 'node') {
  // Since the address can be from a User
  // or ia Node Address, we need to choose the right
  // ID: node version or user ID
  $field = ($type == 'node' ? 'vid': 'uid');

  if (!empty($address)) {
    if (empty($address['aid'])) {
      $aid_sql = '';
      $aid_sql2 = '';
    }
    else {
      // Instead of create INSERT and UPDATE SQL
      // instrauctions, we DELETE (if exists) the given
      // Address and create another one in its place
      db_query('DELETE FROM {address} WHERE aid = %d', $address['aid']);
      $aid_sql = ', aid';
      $aid_sql2 = ', %d';
    }

    // If this address is the Primary, change all other address
    // to NOT primary
    if (!empty($address['is_primary'])) {
      db_query("UPDATE {address} SET is_primary = 0
        WHERE is_primary = 1 AND eid = %d AND atype = '%s'",
        $object->$field, $type);
    }

    // Let other modules change the standard behaviour
    module_invoke_all('addressapi', 'save', $address);

    db_query("INSERT INTO {address}
      (atype, eid, aname, street,
      additional, city, province, postal_code, country, is_primary". $aid_sql .")
      VALUES ('%s', %d, '%s', '%s',
      '%s', '%s', '%s', '%s', '%s', %d". $aid_sql2 .")",
      $type,
      $object->$field,
      (empty($address['aname'])        ? '' : $address['aname']),
      (empty($address['street'])       ? '' : $address['street']),
      (empty($address['additional'])   ? '' : $address['additional']),
      (empty($address['city'])         ? '' : $address['city']),
      (empty($address['province'])     ? '' : strtoupper($address['province'])),
      (empty($address['postal_code'])  ? '' : $address['postal_code']),
      (empty($address['country'])      ? '' : $address['country']),
      (empty($address['is_primary'])   ? 0  : $address['is_primary']),
      (empty($address['aid'])          ? 0  : $address['aid'])
    );
  }
}

/**
 * Create a list of states from a given country.
 *
 * @param $country
 *   String. The country code
 * @param $string
 *   String (optional). The state name typed by user
 * @return
 *   Javascript array. List of states
 */
function _address_autocomplete($country, $string = '') {
  $matches  = array();

  // Check if the country code is there
  if ($country) {

    $string   = strtolower($string);
    $string   = '/^'. $string .'/';

    $provinces   = _address_province_get($country);

    // Get only the first 5 provinces that matches
    // partially with the given piece of text
    if (!empty($provinces)) {
      while (list($code, $name) = each($provinces)) {
        if ($counter < 5) {
          if (preg_match($string, strtolower($name))) {
            $matches[$code] = strtolower($name);
            ++$counter;
          }
        }
      }
    }
  }
  // Print the results as a JS array.
  echo drupal_to_js($matches);

  // Finish the page. Its necessary to not continue
  // to build a regular page
  exit();
}

/**
 * List all countries on Planet! :)
 *
 * It uses the ISO notation.
 * See http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
 * or http://www.iso.org/iso/country_codes/iso_3166_code_lists/english_country_names_and_code_elements.htm
 * for further info.
 *
 * @param $upper
 *   Boolean (optional). When TRUE, the country codes will
 *   be totally in Upper Case. Its the default ISO code,
 *   but the files and function are all named with lower
 *   case, so its better to return lower case by default
 * @return
 *   Array. 'COUNTRY CODE' => 'COUNTRY CODE' pairs as layed out in
 *   ISO 3166-1 alpha-2
 */
function _address_country_get($upper = FALSE) {
  $countries = array(
    'ad' => t('Andorra'),
    'ae' => t('United Arab Emirates'),
    'af' => t('Afghanistan'),
    'ag' => t('Antigua and Barbuda'),
    'ai' => t('Anguilla'),
    'al' => t('Albania'),
    'am' => t('Armenia'),
    'an' => t('Netherlands Antilles'),
    'ao' => t('Angola'),
    'aq' => t('Antarctica'),
    'ar' => t('Argentina'),
    'as' => t('American Samoa'),
    'at' => t('Austria'),
    'au' => t('Australia'),
    'aw' => t('Aruba'),
    'ax' => t('Aland Islands'),
    'az' => t('Azerbaijan'),
    'ba' => t('Bosnia and Herzegovina'),
    'bb' => t('Barbados'),
    'bd' => t('Bangladesh'),
    'be' => t('Belgium'),
    'bf' => t('Burkina Faso'),
    'bg' => t('Bulgaria'),
    'bh' => t('Bahrain'),
    'bi' => t('Burundi'),
    'bj' => t('Benin'),
    'bm' => t('Bermuda'),
    'bn' => t('Brunei'),
    'bo' => t('Bolivia'),
    'br' => t('Brazil'),
    'bs' => t('Bahamas'),
    'bt' => t('Bhutan'),
    'bv' => t('Bouvet Island'),
    'bw' => t('Botswana'),
    'by' => t('Belarus'),
    'bz' => t('Belize'),
    'ca' => t('Canada'),
    'cc' => t('Cocos (Keeling) Islands'),
    'cd' => t('Congo (Kinshasa)'),
    'cf' => t('Central African Republic'),
    'cg' => t('Congo (Brazzaville)'),
    'ch' => t('Switzerland'),
    'ci' => t('Ivory Coast'),
    'ck' => t('Cook Islands'),
    'cl' => t('Chile'),
    'cm' => t('Cameroon'),
    'cn' => t('China'),
    'co' => t('Colombia'),
    'cr' => t('Costa Rica'),
    'cs' => t('Serbia And Montenegro'),
    'cu' => t('Cuba'),
    'cv' => t('Cape Verde'),
    'cx' => t('Christmas Island'),
    'cy' => t('Cyprus'),
    'cz' => t('Czech Republic'),
    'de' => t('Germany'),
    'dj' => t('Djibouti'),
    'dk' => t('Denmark'),
    'dm' => t('Dominica'),
    'do' => t('Dominican Republic'),
    'dz' => t('Algeria'),
    'ec' => t('Ecuador'),
    'ee' => t('Estonia'),
    'eg' => t('Egypt'),
    'eh' => t('Western Sahara'),
    'er' => t('Eritrea'),
    'es' => t('Spain'),
    'et' => t('Ethiopia'),
    'fi' => t('Finland'),
    'fj' => t('Fiji'),
    'fk' => t('Falkland Islands'),
    'fm' => t('Micronesia'),
    'fo' => t('Faroe Islands'),
    'fr' => t('France'),
    'ga' => t('Gabon'),
    'gd' => t('Grenada'),
    'ge' => t('Georgia'),
    'gf' => t('French Guiana'),
    'gg' => t('Guernsey'),
    'gh' => t('Ghana'),
    'gi' => t('Gibraltar'),
    'gl' => t('Greenland'),
    'gm' => t('Gambia'),
    'gn' => t('Guinea'),
    'gp' => t('Guadeloupe'),
    'gq' => t('Equatorial Guinea'),
    'gr' => t('Greece'),
    'gs' => t('South Georgia and the South Sandwich Islands'),
    'gt' => t('Guatemala'),
    'gu' => t('Guam'),
    'gw' => t('Guinea-Bissau'),
    'gy' => t('Guyana'),
    'hk' => t('Hong Kong S.A.R., China'),
    'hm' => t('Heard Island and McDonald Islands'),
    'hn' => t('Honduras'),
    'hr' => t('Croatia'),
    'ht' => t('Haiti'),
    'hu' => t('Hungary'),
    'id' => t('Indonesia'),
    'ie' => t('Ireland'),
    'il' => t('Israel'),
    'im' => t('Isle of Man'),
    'in' => t('India'),
    'io' => t('British Indian Ocean Territory'),
    'iq' => t('Iraq'),
    'ir' => t('Iran'),
    'is' => t('Iceland'),
    'it' => t('Italy'),
    'je' => t('Jersey'),
    'jm' => t('Jamaica'),
    'jo' => t('Jordan'),
    'jp' => t('Japan'),
    'ke' => t('Kenya'),
    'kg' => t('Kyrgyzstan'),
    'kh' => t('Cambodia'),
    'ki' => t('Kiribati'),
    'km' => t('Comoros'),
    'kn' => t('Saint Kitts and Nevis'),
    'kp' => t('North Korea'),
    'kr' => t('South Korea'),
    'kw' => t('Kuwait'),
    'ky' => t('Cayman Islands'),
    'kz' => t('Kazakhstan'),
    'la' => t('Laos'),
    'lb' => t('Lebanon'),
    'lc' => t('Saint Lucia'),
    'li' => t('Liechtenstein'),
    'lk' => t('Sri Lanka'),
    'lr' => t('Liberia'),
    'ls' => t('Lesotho'),
    'lt' => t('Lithuania'),
    'lu' => t('Luxembourg'),
    'lv' => t('Latvia'),
    'ly' => t('Libya'),
    'ma' => t('Morocco'),
    'mc' => t('Monaco'),
    'md' => t('Moldova'),
    'me' => t('Montenegro'),
    'mg' => t('Madagascar'),
    'mh' => t('Marshall Islands'),
    'mk' => t('Macedonia'),
    'ml' => t('Mali'),
    'mm' => t('Myanmar'),
    'mn' => t('Mongolia'),
    'mo' => t('Macao S.A.R., China'),
    'mp' => t('Northern Mariana Islands'),
    'mq' => t('Martinique'),
    'mr' => t('Mauritania'),
    'ms' => t('Montserrat'),
    'mt' => t('Malta'),
    'mu' => t('Mauritius'),
    'mv' => t('Maldives'),
    'mw' => t('Malawi'),
    'mx' => t('Mexico'),
    'my' => t('Malaysia'),
    'mz' => t('Mozambique'),
    'na' => t('Namibia'),
    'nc' => t('New Caledonia'),
    'ne' => t('Niger'),
    'nf' => t('Norfolk Island'),
    'ng' => t('Nigeria'),
    'ni' => t('Nicaragua'),
    'nl' => t('Netherlands'),
    'no' => t('Norway'),
    'np' => t('Nepal'),
    'nr' => t('Nauru'),
    'nu' => t('Niue'),
    'nz' => t('New Zealand'),
    'om' => t('Oman'),
    'pa' => t('Panama'),
    'pe' => t('Peru'),
    'pf' => t('French Polynesia'),
    'pg' => t('Papua New Guinea'),
    'ph' => t('Philippines'),
    'pk' => t('Pakistan'),
    'pl' => t('Poland'),
    'pm' => t('Saint Pierre and Miquelon'),
    'pn' => t('Pitcairn'),
    'pr' => t('Puerto Rico'),
    'ps' => t('Palestinian Territory'),
    'pt' => t('Portugal'),
    'pw' => t('Palau'),
    'py' => t('Paraguay'),
    'qa' => t('Qatar'),
    're' => t('Reunion'),
    'ro' => t('Romania'),
    'rs' => t('Serbia'),
    'ru' => t('Russia'),
    'rw' => t('Rwanda'),
    'sa' => t('Saudi Arabia'),
    'sb' => t('Solomon Islands'),
    'sc' => t('Seychelles'),
    'sd' => t('Sudan'),
    'se' => t('Sweden'),
    'sg' => t('Singapore'),
    'sh' => t('Saint Helena'),
    'si' => t('Slovenia'),
    'sj' => t('Svalbard and Jan Mayen'),
    'sk' => t('Slovakia'),
    'sl' => t('Sierra Leone'),
    'sm' => t('San Marino'),
    'sn' => t('Senegal'),
    'so' => t('Somalia'),
    'sr' => t('Suriname'),
    'st' => t('Sao Tome and Principe'),
    'sv' => t('El Salvador'),
    'sy' => t('Syria'),
    'sz' => t('Swaziland'),
    'tc' => t('Turks and Caicos Islands'),
    'td' => t('Chad'),
    'tf' => t('French Southern Territories'),
    'tg' => t('Togo'),
    'th' => t('Thailand'),
    'tj' => t('Tajikistan'),
    'tk' => t('Tokelau'),
    'tl' => t('East Timor'),
    'tm' => t('Turkmenistan'),
    'tn' => t('Tunisia'),
    'to' => t('Tonga'),
    'tr' => t('Turkey'),
    'tt' => t('Trinidad and Tobago'),
    'tv' => t('Tuvalu'),
    'tw' => t('Taiwan'),
    'tz' => t('Tanzania'),
    'ua' => t('Ukraine'),
    'ug' => t('Uganda'),
    'uk' => t('United Kingdom'),
    'um' => t('United States Minor Outlying Islands'),
    'us' => t('United States'),
    'uy' => t('Uruguay'),
    'uz' => t('Uzbekistan'),
    'va' => t('Vatican'),
    'vc' => t('Saint Vincent and the Grenadines'),
    've' => t('Venezuela'),
    'vg' => t('British Virgin Islands'),
    'vi' => t('U.S. Virgin Islands'),
    'vn' => t('Vietnam'),
    'vu' => t('Vanuatu'),
    'wf' => t('Wallis and Futuna'),
    'ws' => t('Samoa'),
    'ye' => t('Yemen'),
    'yt' => t('Mayotte'),
    'za' => t('South Africa'),
    'zm' => t('Zambia'),
    'zw' => t('Zimbabwe'),
  );

  // In fact, the ISO codes for countries are all Upper Case.
  // So, if someone needs the list as the official records,
  // it will convert.
  if (!empty($upper)) {
    $countries = array_change_key_case($countries, CASE_UPPER);
  }
  // Sort the list and return
  natcasesort($countries);
  return $countries;
}

/**
 * It returns a list of form fields for a single address.
 *
 * @ingroup form
 * @param &$form_state
 *   Array. The current form structure.
 * @param $fields
 *   Array. Values where each value is one of 'street', 'city',
 *   'province', 'postal_code', or 'country'. The presence of
 *   values in this array determines which fields will be served
 *   in the address form generated by a call to this function.
 *   If this array is empty, all fields are generated.
 * @param $values
 *   Array. Each key is one of the address fields: 'street', 'additional',
 *   'city', 'province', 'postal_code', 'country' and each value is
 *   a prefilled value for the given field.
 *
 * @return
 *   An address form based on the parameters specified.  If the $fields array is empty, then the
 *   function returns a form in which all possible fields are served as optional form items.
 *
 * @see _address_form_validate()
 * @see _address_form_submit()
 */
function _address_form(&$form, $group = '', $values = array()) {
  // If no field was specified, use all
//   if (empty($fields)) {
//     $fields = array(
//       'aname'       => 1,
//       'street'      => 1,
//       'city'        => 1,
//       'province'    => 1,
//       'postal_code' => 1,
//       'country'     => 1
//     );
//   }
  $fields = module_invoke_all('address_fields_api', 'group');
  $fields = $fields[$group];

  // Generate the Address fieldset
  $form['address'] = array(
    '#tree'       => TRUE,
  );

  for ($a = 0; $a < 1; $a++) {
    // Address fieldset
    $form['address'][$a] = array(
      '#attributes' => array('class' => 'address'),
      '#title'      => t('Address %number', array('%number' => $index + 1)),
      '#tree'       => TRUE,
      '#type'       => 'fieldset',
    );

    // If its a existing address, save the Address ID
    // for further processing
    if (!empty($values['aid'])) {
      $form['address'][$a]['aid'] = array(
        '#type'   => 'hidden',
        '#value'  => $values['aid']
      );
    }

    // Let users select if the address is the primary
    if ($fields['is_primary'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['is_primary'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['is_primary']) ? $values['is_primarys'] : '',
      );
    }
    elseif (!empty($fields['is_primary'])) {
      $form['address'][$a]['is_primary'] = array(
        '#type'           => 'checkbox',
        '#title'          => t('Default address'),
        '#default_value'  => isset($values['is_primary']) ? $values['is_primary'] : ''
      );
    }

    // Adds the Address Name (Home, Office, Rio de Janeiro...)
    if ($fields['aname'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['aname'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['aname']) ? $values['aname'] : '',
      );
    }
    elseif (!empty($fields['aname'])) {
      $form['address'][$a]['aname'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Address name'),
        '#default_value'  => isset($values['aname']) ? $values['aname'] : '',
        '#size'           => 64,
        '#maxlength'      => 64,
        '#description'    => t('e.g. a place of business, venue, meeting point'),
        '#attributes'     => NULL,
        '#required'       => ($fields['aname'] == ADDRESS_FIELD_REQUIRED)
      );
    }

    // Adds the Country
    if ($fields['country'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['country'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['country']) ? $values['country'] : '',
      );
    }
    elseif (!empty($fields['country'])) {
      $countries = array('' => '') + _address_country_get();

      $form['address'][$a]['country'] = array(
        '#type'           => 'select',
        '#title'          => t('Country'),
        '#default_value'  => isset($values['country']) ? $values['country'] : '',
        '#options'        => $countries,
        '#description'    => NULL,
        '#extra'          => 0,
        '#multiple'       => FALSE,
        '#required'       => ($fields['country'] == ADDRESS_FIELD_REQUIRED)
      );
    }

    // Adds the Province field
    if ($fields['province'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['province'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['province']) ? $values['province'] : '',
      );
    }
    elseif (!empty($fields['province'])) {
      $form['address'][$a]['province'] = array(
  //       '#autocomplete_path'  => 'admin/settings/address/autocomplete',
        '#default_value'  => isset($values['province']) ? $values['province'] : '',
        '#maxlength'      => 64,
        '#required'       => ($fields['province'] == ADDRESS_FIELD_REQUIRED),
        '#size'           => 30,
        '#title'          => t('State / Province'),
        '#type'           => 'textfield',
      );
      $form['#validate'][] = '_address_province_validate';
    }

    // Adds the City
    if ($fields['city'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['city'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['city']) ? $values['city'] : '',
      );
    }
    elseif (!empty($fields['city'])) {
      $form['address'][$a]['city'] = array(
        '#type'           => 'textfield',
        '#title'          => t('City'),
        '#default_value'  => isset($values['city']) ? $values['city'] : '',
        '#size'           => 64,
        '#maxlength'      => 64,
        '#description'    => NULL,
        '#attributes'     => NULL,
        '#required'       => ($fields['city'] == ADDRESS_FIELD_REQUIRED)
      );
    }

    // Adds the Streets and the Additional fields
    if ($fields['street'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['street'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['street']) ? $values['street'] : '',
      );
      $form['address'][$a]['additional'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['additional']) ? $values['additional'] : '',
      );
    }
    elseif (!empty($fields['street'])) {
      $form['address'][$a]['street'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Street'),
        '#default_value'  => isset($values['street']) ? $values['street'] : '',
        '#size'           => 64,
        '#maxlength'      => 64,
        '#required'       => ($fields['street'] == ADDRESS_FIELD_REQUIRED)
      );
      $form['address'][$a]['additional'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Additional'),
        '#default_value'  => isset($values['additional']) ? $values['additional'] : '',
        '#size'           => 64,
        '#maxlength'      => 64
      );
    }

    // Adds the Postal Code
    if ($fields['postal_code'] == ADDRESS_FIELD_HIDDEN) {
      $form['address'][$a]['postal_code'] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values['postal_code']) ? $values['postal_code'] : '',
      );
    }
    elseif (!empty($fields['postal_code'])) {
      $form['address'][$a]['postal_code'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Postal code'),
        '#default_value'  => isset($values['postal_code']) ? $values['postal_code'] : '',
        '#size'           => 16,
        '#maxlength'      => 16,
        '#required'       => ($fields['postal_code'] == ADDRESS_FIELD_REQUIRED)
      );
    }
  }

  // Set a different layout for address forms
//   $form['#theme'] = 'address_form';
}

/**
 * Get available states.
 *
 * @param $country
 *   String (optional). The 2-digit country code
 * @return
 *   Array. If $country is passed, then return an array
 *   of states for that country. If nothing is passed then return
 *   an array of countrys who have states, where each country contains
 *   an array of states.
 */
function _address_province_get($country = NULL) {
  static $provinces;

  // Get a list of countries
  $countries_all = _address_country_get();

  // Test if its needed to update the province list
  if (empty($country) and empty($provinces)) {
    // Get the countries list
    $countries = array_keys($countries_all);
    $update = TRUE;
  }
  elseif (!empty($country) and $countries_all[$country] and empty($provinces[$country])) {
    $countries[] = $country;
    $update = TRUE;
  }

  if (!empty($update)) {
    foreach ($countries as $country_code) {
      // Load country specifice code .inc file if it exists.
      // For example, if country_code for U.S. == 'us', load 'address.us.inc'
      include_once ADDRESS_PATH .'/countries/'. $country_code .'.inc';

      // If the country have a province list, load it
      $function = 'address_province_list_'. $country_code;
      if (function_exists($function)) {
        $provinces[$country_code] = $function();
      }
    }
  }

  // Return the states of a single country, if any
  if (!empty($country)) {
    if (isset($provinces[$country])) {
      return $provinces[$country];
    }
    else {
      return array();
    }
  }
  else {
    return $provinces;
  }
}

/**
 * Validate the province field
 */
function _address_province_validate($form, &$form_state) {
  // Check if its a valid province.
  // It should be the Province code listed on the
  // given COUNTRY.inc file
  $form_values = $form_state['values'];

  foreach (element_children($form_values['address']) as $a) {
    if ($provinces = _address_province_get($form_values['address'][$a]['country']) and
        empty($provinces[strtoupper($form_values['address'][$a]['province'])])) {
      form_set_error("address][$a][province", t('Invalid province. Try to use the province code.'));
    }
  }
}

/**
 * Generates HTML for the passed address.
 *
 * @ingroup themeable
 * @param $address
 *   Array. A single address with the following fields (generally, but it can have more):
 *   - 'street'       => A string representing the street
 *   - 'additional'   => A string for any additional portion of the street
 *   - 'city'         => A string for the city name
 *   - 'province'     => The standard postal abbreviation for the province
 *   - 'country'      => The two-letter ISO code for the country of the address (REQUIRED)
 *   - 'postal_code'  => The international postal code for the address
 * @param $hide
 *   Array (optional). The values are the address fields to suppress in the themed display.
 */
function theme_address($address, $hide = array()) {
  // Check if it have at least one field to be displayed.
  // If not, return '' and stop everything
  foreach ($hide as $field) {
    if (!empty($address[$field])) {
      unset($address[$field]);
    }
  }

  // If all fields are hidden, return ''
  if (empty($address)) {
    return '';
  }

  // Besides being the Drupal Address info,
  // its possible to be used by VCard
  $output = '<div class="address vcard">';

  // Address name, if any
  if (!empty($address['aname'])) {
    $output .= '<div>'. theme('placeholder', $address['aname']);

    // If its the default address, point it
    if (!empty($address['is_primary'])) {
      $output .= ' ('. t('default') .')';
    }
    $output .='</div>';
  }

  // Street and Addicional info
  if (!empty($address['street'])) {
    $output .= '<div class="street-address">'. $address['street'];
    if (!empty($address['additional']) and !in_array('street', $hide)) {
      $output .= ' '. $address['additional'];
    }
    $output .='</div>';
  }

  // City
  if (!empty($address['city'])) {
    $city_province_postal[] = '<span class="city">'. $address['city'] .'</span>';
  }

  // Province
  if (!empty($address['province'])) {
    $city_province_postal[] = '<span class="region">'. $address['province'] .'</span>';
  }

  // Country
  if (!empty($address['country'])) {
    $countries = _address_country_get();
    $city_province_postal[] = '<span class="country-name">'. t($countries[$address['country']]) .'</span>';
  }
  // City, Province and Country are all placed on the same line,
  // separated by commas.
  if (!empty($city_province_postal)) {
    $output .= implode(', ', $city_province_postal);
  }

  // Postal code
  if (!empty($address['postal_code']) and !in_array('postal_code', $hide)) {
    $output .= $city_province_postal[] = '<div class="postal-code">'. $address['postal_code'] .'</div>';
  }

  $output .= '</div>';

  return $output;
}

/**
 * Theme the Address form
 *
 * @ingroup themeable
 * @param &$form
 *   Array. The form structure
 */
function theme_address_form(&$form) {
  // If the country and state fields are present,
  // enable the extra JS
//   if (!empty($form['province'])
//       and $form['province']['#type'] != 'hidden'
//       and $form['country']['#type'] != 'hidden') {
//     global $base_url;
//     drupal_add_js(array('absPath' => $base_url), 'setting');
//     drupal_add_js(drupal_get_path('module', 'address') .'/address.js');
//   }

  // The required field notation
  $req_str = '<span class="form-required" title="'. t('This field is required.') .'">*</span>';

  foreach (element_children($form) as $field_name) {
    $col = array();
    if ($form[$field_name]['#type'] == 'markup') {
      $col[] = array('data' => $form[$field_name]['#value'], 'colspan' => 2);
    }
    elseif ($form[$field_name]['#type'] != 'hidden') {
      $required = !empty($form[$field_name]['#required']) ? $req_str : '';

      // Check if the element has a title
      if (!empty($form[$field_name]['#title'])) {
        $col[] = array(
          'align' => 'right',
          'data'  => '<div class="form-item"><label'. ($form[$field_name]['#id'] ?
          ' for="'. $form[$field_name]['#id'] .'" ' : '') .'>'.
          filter_xss_admin($form[$field_name]['#title']) .": $required</label></div>"
        );
        unset($form[$field_name]['#title']);
      }
      else {
        $col[] = array('');
      }

      // The field itselt
      $col[] = array(
        'align' => 'left',
        'data' => drupal_render($form[$field_name])
      );

      $rows[] = array('data' => $col);
    }
  }

  $output = theme('table', NULL, $rows);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Create a single line address. Usefull for some labels.
 *
 * @param $address
 *   Array. The address parts. @see theme_address()
 * @return
 *   String. The single line address
 */
function theme_address_singleline($address) {
  // Check if its a valied address
  if (empty($address)) {
    return '';
  }

  $address = '';

  // Add the streets
  if (!empty($address['street'])) {
    $address .= $address['street'];
  }

  // Add the city
  if (!empty($address['city'])) {
    if (!empty($address['street'])) {
      $address .= ', ';
    }
    $address .= $address['city'];
  }

  // Add the state / province
  if (!empty($address['province'])) {
    if (!empty($address['street']) or !empty($address['city'])) {
      $address .= ', ';
    }
    $address .= $address['province'];
  }

  // Add the Postal code
  if (!empty($address['postal_code'])) {
    if (!empty($address)) {
      $address .= ' ';
    }
    $address .= $address['postal_code'];
  }

  // Add the country
  if (!empty($address['country'])) {
    $address .= ', '. $address['country'];
  }

  return $address;
}
