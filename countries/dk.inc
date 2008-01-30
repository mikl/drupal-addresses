<?php
// $Id$

// Denmark

/**
 * Implementation of hook_province_list().
 *
 * Its a hook from Addresses module to list all
 * states/provinces/teritories of a given contry
 *
 * @return
 *   Array. states where the keys are the state
 *   code and the value is the state name
 */
function addresses_province_list_dk() {
  return array(
    'CC' => t('Copenhagen (municipality)'),
    'FC' => t('Frederiksberg (municipality)'),
    'CO' => t('Copenhagen'),
    'FR' => t('Frederiksborg'),
    'RO' => t('Roskilde'),
    'WZ' => t('West Zealand'),
    'ST' => t('Storstrom'),
    'FU' => t('Funen'),
    'SJ' => t('South Jutland'),
    'RB' => t('Ribe'),
    'VK' => t('Vejle'),
    'RK' => t('Ringkjobing'),
    'VB' => t('Viborg'),
    'NJ' => t('North Jutland'),
    'AR' => t('Arhus'),
    'BH' => t('Bornholm'),
    'GL' => t('Greenland'),
    'FO' => t('Faroe Islands')
  );
}
