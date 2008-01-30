<?php
// $Id$

// Canada

/**
 * Returns an associative array of states/territories where
 *   -> the keys are integers starting from 1
 *   -> the values are the English names for those states/territories
 *
 * The states are grouped together at the beginning of the array and sorted
 * alphabetically.
 *
 * The territories are grouped together at the end of the array and sorted
 * alphabetically.
 *
 */
function addresses_province_list_ca() {
  return array(
    'AB' => t('Alberta'),
    'BC' => t('British Columbia'),
    'MB' => t('Manitoba'),
    'NB' => t('New Brunswick'),
    'NL' => t('Newfoundland and Labrador'),
    'NS' => t('Nova Scotia'),
    'ON' => t('Ontario'),
    'PE' => t('Prince Edward Island'),
    'QC' => t('Quebec'),
    'SK' => t('Saskatchewan'),
    'NT' => t('Northwest Territories'),
    'NU' => t('Nunavut'),
    'YT' => t('Yukon Territory')
  );
}
