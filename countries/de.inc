<?php
// $Id$

// Germany

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
