<?php
// $Id$
/**
 * @author Bruno Massa
 * @file addresses.settings.inc
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
    $form['#validate'][] = '_addresses_province_validate';
  }

  // Adds the City
  if (!empty($fields['city'])) {
    $form['city'] = array(
      '#type'           => 'textfield',
      '#title'          => t('City'),
      '#default_value'  => isset($values['city']) ? $values['city'] : '',
      '#size'           => 50,
      '#maxlength'      => 255,
      '#description'    => NULL,
      '#attributes'     => NULL,
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
    $form['additional'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Additional'),
      '#default_value'  => isset($values['additional']) ? $values['additional'] : '',
      '#size'           => 50,
      '#maxlength'      => 255
    );
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
 * Modules settings page
 *
 * @ingroup form
 */
function _addresses_admin(&$form_state) {
  $countries = _addresses_country_get();

  // List of countries that the site allow
  $form['addresses_country_list'] = array(
    '#default_value'  => variable_get('addresses_country_list', array_keys(_addresses_country_get())),
    '#description'    => t('You might want to limit the country lists. Select the countries you want.'),
    '#multiple'       => TRUE,
    '#options'        => $countries,
    '#type'           => 'select',
    '#title'          => t('Possible country'),
  );

  // Let users to change the address formats
  array_unshift($countries,  t('Default'));
  $countries_max = count($countries) / 4;
  foreach ($countries as $country_code => $country) {
    $columns[++$country_num / $countries_max][] = l($country, 'admin/settings/address/format/'. $country_code);
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
