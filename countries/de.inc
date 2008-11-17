<?php
// $Id$

/**
 * @file
 * "Germany" specific data
 */

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
/**
 * Implementation of hook_province_list().
 *
 * Its a hook from Addresses module to list all
 * states/provinces/teritories of a given country
 *
 * @return
 *   Array. states where the keys are the state
 *   code and the value is the state name
 */
function addresses_province_list_de() {
  return array(
    'BB' => t('Brandenburg'),
    'BE' => t('Berlin'),
    'BW' => t('Baden-Württemberg'),
    'BY' => t('Bayern'),
    'HB' => t('Bremen'),
    'HE' => t('Hessen'),
    'HH' => t('Hamburg'),
    'MV' => t('Mecklenburg-Vorpommern'),
    'NI' => t('Niedersachsen'),
    'NW' => t('Nordrhein-Westfalen'),
    'RP' => t('Rheinland-Pfalz'),
    'SH' => t('Schleswig-Holstein'),
    'SL' => t('Saarland'),
    'SN' => t('Sachsen'),
    'ST' => t('Sachsen-Anhalt'),
    'TH' => t('Thüringen')
  );
}
