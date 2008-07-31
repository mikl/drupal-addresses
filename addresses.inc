<?php
// $Id$
/**
 * @author Bruno Massa
 * @file addresses.inc
 * An implementation of a universal API for address manipulation.
 */

/**
 * Modules settings page
 *
 * @ingroup form
 */
function _addresses_admin(&$form_state) {
  $form = array();

  // List of contries that the site allow
  $form['addresses_contry_list'] = array(
    '#default_value'  => variable_get('addresses_contry_list', array_keys(_addresses_country_get())),
    '#description'    => t('You might want to limit the contry lists. Select the contries you want.'),
    '#multiple'       => TRUE,
    '#options'        => _addresses_country_get(),
    '#type'           => 'select',
    '#title'          => t('Possible country'),
  );

  // We will use the this function that automatically
  // save all form fields into global variables
  return system_settings_form($form);
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
function _addresses_address_delete($id, $type = 'address') {
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
function _addresses_address_save($address, $id, $type = 'node') {
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
function _addresses_autocomplete($country, $string = '') {
  $matches  = array();

  // Check if the country code is there
  if ($country) {

    $string   = strtolower($string);
    $string   = '/^'. $string .'/';

    $provinces   = _addresses_province_get($country);

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
 * @param $available
 *   String (optional). A list of contries that are allowed.
 * @param $upper
 *   Boolean (optional). When TRUE, the country codes will
 *   be totally in Upper Case. Its the default ISO code,
 *   but the files and function are all named with lower
 *   case, so its better to return lower case by default
 * @return
 *   Array. 'COUNTRY CODE' => 'COUNTRY CODE' pairs as layed out in
 *   ISO 3166-1 alpha-2
 */
function _addresses_country_get($available = array(), $upper = FALSE) {
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

  if (!empty($available)) {
    foreach ($countries as $ccode => $country) {
      if (empty($available[$ccode])) {
        unset($countries[$ccode]);
      }
    }
  }

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
 * @param $group
 *   String. The variable that contains the group of fields that
 *   will be used on this address.
 * @param $values
 *   Array (optional). Each key is one of the address fields: 'street',
 *   'additional', 'city', 'province', 'postal_code', 'country' and each
 *   value is a prefilled value for the given field.
 *
 * @return
 *   An address form based on the parameters specified.  If the $fields array is empty, then the
 *   function returns a form in which all possible fields are served as optional form items.
 *
 * @see _addresses_form_validate()
 * @see _addresses_form_submit()
 */
function _addresses_form(&$form, $fields, $values = array()) {
  // Generate the Global Address fieldset or only the
  // form hierarchy
  if (!empty($fields['master_fieldset'])) {
    $form['addresses'] = array(
      '#collapsible'  => TRUE,
      '#collapsed'    => TRUE,
      '#title'        => t('Addresses'),
      '#type'         => 'fieldset',
    );
  }
  $form['addresses']['#tree'] = TRUE;

  // At least one address form should exist
  if (empty($fields['qty'])) {
    $fields['qty'] = 1;
  }

  for ($a = 1; $a <= $fields['qty']; $a++) {
    // Address fieldset
    if (!empty($fields['local_fieldset'])) {
      $form['addresses'][$a] = array(
        '#collapsible'  => TRUE,
        '#title'        => $a + 1,
        '#type'         => 'fieldset',
      );
    }
    $form['addresses'][$a]['#tree'] = TRUE;

    // If its a existing address, save the Address ID
    // for further processing
    if (!empty($values[$a]['aid'])) {
      $form['addresses'][$a]['aid'] = array(
        '#type'   => 'hidden',
        '#value'  => $values[$a]['aid']
      );
    }

    // Get other fields from hook_addressesfieldsapi
    $form['addresses'] = array_merge(
      $form['addresses'],
      module_invoke_all('addressesfieldapi', 'form', $fields, $values)
    );
  }

  return $form;
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
function _addresses_province_get($country = NULL) {
  static $provinces;

  // Get a list of countries
  $countries_all = _addresses_country_get();

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
      // For example, if country_code for U.S. == 'us', load 'addresses.us.inc'
      include_once drupal_get_path('module', 'addresses') .'/countries/'. $country_code .'.inc';

      // If the country have a province list, load it
      $function = 'addresses_province_list_'. $country_code;
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
function _addresses_province_validate($form, &$form_state) {
  // Check if its a valid province.
  // It should be the Province code listed on the
  // given COUNTRY.inc file
  foreach (element_children($form_state['values']['addresses']) as $a) {
    if ($provinces = _addresses_province_get($form_state['values']['addresses'][$a]['country'])
        and empty($provinces[strtoupper($form_state['values']['addresses'][$a]['province'])])) {
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
function theme_addresses($address, $hide = array()) {
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
  $output = '<div class="address vcard adr">';

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
    $city_province_postal[] = '<span class="city locality">'. $address['city'] .'</span>';
  }

  // Province
  if (!empty($address['province'])) {
    $city_province_postal[] = '<span class="region">'. $address['province'] .'</span>';
  }

  // Country
  if (!empty($address['country'])) {
    $countries = _addresses_country_get();
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
 * Format a date selection element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: title, value, options, description, required and attributes.
 * @return
 *   A themed HTML string representing the date selection boxes.
 *
 * @ingroup themeable
 */
function theme_addresses_elements($element) {
  return theme('form_element', $element, '<div class="container-inline">'. $element['#children'] .'</div>');
}

/**
 * Theme the Address form
 *
 * @ingroup themeable
 * @param &$form
 *   Array. The form structure
 */
function theme_addresses_form(&$form) {
  // If the country and state fields are present,
  // enable the extra JS
//   if (!empty($form['province'])
//       and $form['province']['#type'] != 'hidden'
//       and $form['country']['#type'] != 'hidden') {
//     global $base_url;
//     drupal_add_js(array('absPath' => $base_url), 'setting');
//     drupal_add_js(drupal_get_path('module', 'address') .'/addresses.js');
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
 * @ingroup themeable
 * @param $address
 *   Array. The address parts. see theme_address()
 * @return
 *   String. The single line address
 */
function theme_addresses_singleline($address) {
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
