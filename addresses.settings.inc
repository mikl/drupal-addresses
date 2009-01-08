<?php
// $Id$
/**
 * @author Bruno Massa
 * @file
 * All settings functions for Addresses module.
 */

/**
 * It splits the _addresses_addressesfieldapi_form into more pieces,
 * reducing the memory consumption on non related pages.
 *
 * @ingroup form
 */
function _addresses_addressesfieldapi_form($fields = array(), $values = array()) {
  // Let users select if the address is the primary
  if (!empty($fields['is_primary'])) {
    $form['is_primary'] = array(
      '#type'           => 'checkbox',
      '#title'          => t('Default address'),
      '#default_value'  => isset($values['is_primary']) ? $values['is_primary'] : ''
    );
  }

  // Adds the Address Name (Home, Office, Rio de Janeiro...)
  if (!empty($fields['aname'])) {
    $form['aname'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Address name'),
      '#default_value'  => isset($values['aname']) ? $values['aname'] : '',
      '#size'           => 50,
      '#maxlength'      => 75,
      '#description'    => t('e.g. a place of business, venue, meeting point'),
      '#attributes'     => NULL,
      '#required'       => ($fields['aname'] == ADDRESSES_FIELD_REQUIRED)
    );
  }

  // Adds the Country
  if (!empty($fields['country'])) {
    // Get a list of enabled countries
    $countries = array('' => '') +
      _addresses_country_get(variable_get('addresses_country_list', array()));

    $form['country'] = array(
      '#type'           => 'select',
      '#title'          => t('Country'),
      '#default_value'  => isset($values['country']) ? $values['country'] : '',
      '#options'        => $countries,
      '#description'    => NULL,
      '#extra'          => 0,
      '#multiple'       => FALSE,
      '#required'       => ($fields['country'] == ADDRESSES_FIELD_REQUIRED)
    );
  }

  // Adds the Province field
  if (!empty($fields['province'])) {
    $form['province'] = array(
      '#default_value'  => isset($values['province']) ? $values['province'] : '',
      '#maxlength'      => 16,
      '#required'       => ($fields['province'] == ADDRESSES_FIELD_REQUIRED),
      '#size'           => 16,
      '#title'          => t('State / Province'),
      '#type'           => 'textfield',
    );
    $form['#element_validate'][] = '_addresses_province_validate';
  }

  // Adds the City
  if (!empty($fields['city'])) {
    $form['city'] = array(
      '#type'           => 'textfield',
      '#title'          => t('City'),
      '#default_value'  => isset($values['city']) ? $values['city'] : '',
      '#size'           => 50,
      '#maxlength'      => 255,
      '#required'       => ($fields['city'] == ADDRESSES_FIELD_REQUIRED)
    );
  }

  // Adds the Streets and the Additional fields
  if (!empty($fields['street'])) {
    $form['street'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Street'),
      '#default_value'  => isset($values['street']) ? $values['street'] : '',
      '#size'           => 50,
      '#maxlength'      => 255,
      '#required'       => ($fields['street'] == ADDRESSES_FIELD_REQUIRED)
    );
    if (!empty($fields['additional'])) {
      $form['additional'] = array(
        '#type'           => 'textfield',
        '#title'          => t('Additional'),
        '#default_value'  => isset($values['additional']) ? $values['additional'] : '',
        '#size'           => 50,
        '#maxlength'      => 255
      );
    }
  }

  // Adds the Postal Code
  if (!empty($fields['postal_code'])) {
    $form['postal_code'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Postal code'),
      '#default_value'  => isset($values['postal_code']) ? $values['postal_code'] : '',
      '#size'           => 16,
      '#maxlength'      => 16,
      '#required'       => ($fields['postal_code'] == ADDRESSES_FIELD_REQUIRED)
    );
  }

  foreach (array_keys($fields) as $ftype) {
    if ($fields[$ftype] == ADDRESSES_FIELD_HIDDEN) {
      $form[$ftype] = array(
        '#type'           => 'hidden',
        '#value'          => isset($values[$ftype]) ? $values[$ftype] : '',
      );
    }
  }

  return $form;
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

    $string   = drupal_strtolower($string);
    $string   = '/^'. $string .'/';

    $provinces   = _addresses_province_get($country);

    // Get only the first 5 provinces that matches
    // partially with the given piece of text
    if (!empty($provinces)) {
      while (list($code, $name) = each($provinces)) {
        if ($counter < 5) {
          if (preg_match($string, drupal_strtolower($name))) {
            $matches[$code] = drupal_strtolower($name);
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
 * Validate the province field
 */
function _addresses_province_validate($form, &$form_state) {
  // Check if its a valid province.
  // It should be the Province code listed on the
  // given COUNTRY.inc file
  if ($province = $form['province']['#value']
      and $country = $form['country']['#value']
      and $provinces = _addresses_province_get($country)
      and empty($provinces[drupal_strtoupper($province)])) {

    // Get the province fieldname
    $field_name = $form['province']['#name'];
    $field_name = drupal_substr($field_name, 0, -1);
    $field_name = preg_replace('/([^]])\[/', '\1][', $field_name);

    $countries = _addresses_country_get();
    form_set_error($field_name, t('Could not find %province as a province from %country. Try to use the province abbreviation or number.',
      array('%province' => $form['province']['#value'],
      '%country' => $countries[$country])));

  }
}

/**
 * Modules settings page
 *
 * @ingroup form
 */
function _addresses_settings(&$form_state) {
  module_load_include('inc', 'addresses');
  $countries    = _addresses_country_get();
  $country_list = variable_get('addresses_country_list', array_keys(_addresses_country_get()));

  // List of countries that the site allow
  $form['addresses_country_list'] = array(
    '#default_value'  => $country_list,
    '#description'    => t('You might want to limit the country lists. Select the countries you want.'),
    '#multiple'       => TRUE,
    '#options'        => $countries,
    '#type'           => 'select',
    '#title'          => t('Possible country'),
  );

  // Let users to change the address formats
  $countries = array_intersect_key($countries, $country_list);
  array_unshift($countries,  t('Default'));
  $countries_max = ceil(count($countries) / 4);
  $country_num = 0;
  foreach ($countries as $country_code => $country) {
    $columns[$country_num++ / $countries_max][] = l($country, 'admin/settings/address/format/'. $country_code);
  }
  foreach (array_keys($columns[0]) as $row) {
    $rows[] = array($columns[0][$row], $columns[1][$row], $columns[2][$row], $columns[3][$row]);
  }
  $form['addresses_format'] = array(
    '#children'       => theme('table', array(), $rows),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,
    '#description'    => t('Change how the addresses are displayed, for each country. The Default is used if the country doesnt have a preset address format.'),
    '#type'           => 'fieldset',
    '#title'          => t('Address formats'),
  );

  // We will use the this function that automatically
  // save all form fields into global variables
  $form = system_settings_form($form);

  $form['buttons']['#weight'] = 10;
  return $form;
}

/**
 * Generate a settings form that will allow admins to choose
 * which addresses fields shuold be used.
 *
 * @param field_values
 *   Array (optional). The default values for each field, if any
 * @return
 *   Array. A form with settings
 * @ingroup form
 */
function _addresses_settings_fields($field_values = array()) {
  $ftypes = module_invoke_all('addressesfieldapi', 'fields');
  foreach ($ftypes as $ftype => $field) {
    // List of address fields
    $form['addresses'][$ftype] = array(
      '#default_value'  => empty($field_values[$ftype]) ? $field['display'] : $field_values[$ftype],
      '#options'        => array(
        ADDRESSES_FIELD_NONE      => '',
        ADDRESSES_FIELD_SHOW      => '',
        ADDRESSES_FIELD_REQUIRED  => '',
        ADDRESSES_FIELD_HIDDEN    => '',
      ),
      '#title'          => $field['title'],
      '#type'           => 'radios',
    );
  }

  $form['addresses']['#theme'] = 'addresses_settings_fields';

  return $form;
}

/**
 * Modules settings page
 *
 * @ingroup form
 */
function _addresses_settings_format(&$form_state, $country) {
  module_load_include('inc', 'addresses');
  $countries = _addresses_country_get();

  if (!$cname = $countries[$country]) {
    $cname    = t('Default');
    $country  = 'default';
  }

  if (!$format_address = variable_get('addresses_format_'. $country, '')) {
    include_once drupal_get_path('module', 'addresses') .'/countries/us.inc';
    $format_address = addresses_address_format_us();
    variable_set('addresses_format_default', $format_address);
  }

  $form['addresses_format_'. $country] = array(
    '#default_value'  => $format_address,
    '#title'          => t('Address Format: %country', array('%country' => $cname)),
    '#type'           => 'textarea',
  );

  // Simulate theme('token_help'), but include two types and
  // erase the global types
  $full_list = token_get_list('addresses_general') + token_get_list('addresses_adr');
  unset($full_list['global']);
  $headers = array(t('Token'), t('Replacement value'));
  $rows = array();
  foreach ($full_list as $key => $category) {
    $rows[] = array(array('data' => drupal_ucfirst($key) .' '. t('tokens'), 'class' => 'region', 'colspan' => 2));
    foreach ($category as $token => $description) {
      $row = array();
      $row[] = '!'. $token .'';
      $row[] = $description;
      $rows[] = $row;
    }
  }

  $output = theme('table', $headers, $rows, array('class' => 'description'));

  $form['token_help'] = array(
    '#value'       => $output,
  );

  return system_settings_form($form);
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
  return theme('form_element', $element, '<div class="addresses-form">'. $element['#children'] .'</div>');
}

/**
 * Print a nice settings table for selecting which address fields
 * should be used.
 *
 * @param $form
 *   Array. The address field settings.
 * @return
 *   String. The single line address
 * @ingroup themeable
 */
function theme_addresses_settings_fields($form) {
  foreach (element_children($form) as $ftype) {
    $field = &$form[$ftype];
    $rows[] = array(
      $field['#title'],
      drupal_render($field[0]),
      drupal_render($field[1]),
      drupal_render($field[2]),
      drupal_render($field[3]),
    );
    unset($form[$ftype]);
  }

  $header = array(t('Field'), t('None'), t('Normal'), t('Required'), t('Hidden'));
  $output = theme('table', $header, $rows);

  $output .= drupal_render($form);

  return $output;
}
