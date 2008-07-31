<?php
// $Id$

/**
 * @file
 * "New Zealand" specific data
 */

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
function addresses_province_list_nz() {
  return array(
    'AUK' => t('Auckland'),
    'BOP' => t('Bay of Plenty'),
    'CAN' => t('Canterbury'),
    'GIS' => t('Gisborne'),
    'HKB' => t("Hawke's Bay"),
    'MBH' => t('Marlborough'),
    'MWT' => t('Manawatu-Wanganui'),
    'NSN' => t('Nelson'),
    'NTL' => t('Northland'),
    'OTA' => t('Otago'),
    'STL' => t('Southland'),
    'TAS' => t('Tasman'),
    'TKI' => t('Taranaki'),
    'WGN' => t('Wellington'),
    'WKO' => t('Waikato'),
    'WTC' => t('West Coast')
  );
}
