<?php
// $Id$

// United States

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
 * Currently not being used, but may be in order to be compatible with CiviCRM
 * TODO: These numeric indices need to be changed to match those in the CiviCRM database
 */
function addresses_province_list_numeric_us() {
  return array(
    '001' => t('Alabama'),
    '002' => t('Alaska'),
    '003' => t('Arizona'),
    '004' => t('Arkansas'),
    '005' => t('California'),
    '006' => t('Colorado'),
    '007' => t('Connecticut'),
    '008' => t('Delaware'),
    '009' => t('District Of Columbia'),
    '010' => t('Florida'),
    '011' => t('Georgia'),
    '012' => t('Hawaii'),
    '013' => t('Idaho'),
    '014' => t('Illinois'),
    '015' => t('Indiana'),
    '016' => t('Iowa'),
    '017' => t('Kansas'),
    '018' => t('Kentucky'),
    '019' => t('Louisiana'),
    '020' => t('Maine'),
    '021' => t('Maryland'),
    '022' => t('Massachusetts'),
    '023' => t('Michigan'),
    '024' => t('Minnesota'),
    '025' => t('Mississippi'),
    '026' => t('Missouri'),
    '027' => t('Montana'),
    '028' => t('Nebraska'),
    '029' => t('Nevada'),
    '030' => t('New Hampshire'),
    '031' => t('New Jersey'),
    '032' => t('New Mexico'),
    '033' => t('New York'),
    '034' => t('North Carolina'),
    '035' => t('North Dakota'),
    '036' => t('Ohio'),
    '037' => t('Oklahoma'),
    '038' => t('Oregon'),
    '039' => t('Pennsylvania'),
    '040' => t('Rhode Island'),
    '041' => t('South Carolina'),
    '042' => t('South Dakota'),
    '043' => t('Tennessee'),
    '044' => t('Texas'),
    '045' => t('Utah'),
    '046' => t('Vermont'),
    '047' => t('Virginia'),
    '048' => t('Washington'),
    '049' => t('West Virginia'),
    '050' => t('Wisconsin'),
    '051' => t('Wyoming'),
    '052' => t('American Samoa'),
    '053' => t('Federated States of Micronesia'),
    '054' => t('Guam'),
    '055' => t('Marshall Islands'),
    '056' => t('Northern Mariana Islands'),
    '057' => t('Palau'),
    '058' => t('Puerto Rico'),
    '059' => t('Virgin Islands')
);
}
