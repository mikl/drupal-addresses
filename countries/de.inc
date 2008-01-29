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
function address_province_list_de() {
  return array(
    'BB' => 'Brandenburg',
    'BE' => 'Berlin',
    'BW' => 'Baden-Württemberg',
    'BY' => 'Bayern',
    'HB' => 'Bremen',
    'HE' => 'Hessen',
    'HH' => 'Hamburg',
    'MV' => 'Mecklenburg-Vorpommern',
    'NI' => 'Niedersachsen',
    'NW' => 'Nordrhein-Westfalen',
    'RP' => 'Rheinland-Pfalz',
    'SH' => 'Schleswig-Holstein',
    'SL' => 'Saarland',
    'SN' => 'Sachsen',
    'ST' => 'Sachsen-Anhalt',
    'TH' => 'Thüringen'
  );
}
