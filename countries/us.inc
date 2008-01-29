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
function address_province_list_numeric_us() {
  return array('001' => 'Alabama',
               '002' => 'Alaska',
               '003' => 'Arizona',
               '004' => 'Arkansas',
               '005' => 'California',
               '006' => 'Colorado',
               '007' => 'Connecticut',
               '008' => 'Delaware',
               '009' => 'District Of Columbia',
               '010' => 'Florida',
               '011' => 'Georgia',
               '012' => 'Hawaii',
               '013' => 'Idaho',
               '014' => 'Illinois',
               '015' => 'Indiana',
               '016' => 'Iowa',
               '017' => 'Kansas',
               '018' => 'Kentucky',
               '019' => 'Louisiana',
               '020' => 'Maine',
               '021' => 'Maryland',
               '022' => 'Massachusetts',
               '023' => 'Michigan',
               '024' => 'Minnesota',
               '025' => 'Mississippi',
               '026' => 'Missouri',
               '027' => 'Montana',
               '028' => 'Nebraska',
               '029' => 'Nevada',
               '030' => 'New Hampshire',
               '031' => 'New Jersey',
               '032' => 'New Mexico',
               '033' => 'New York',
               '034' => 'North Carolina',
               '035' => 'North Dakota',
               '036' => 'Ohio',
               '037' => 'Oklahoma',
               '038' => 'Oregon',
               '039' => 'Pennsylvania',
               '040' => 'Rhode Island',
               '041' => 'South Carolina',
               '042' => 'South Dakota',
               '043' => 'Tennessee',
               '044' => 'Texas',
               '045' => 'Utah',
               '046' => 'Vermont',
               '047' => 'Virginia',
               '048' => 'Washington',
               '049' => 'West Virginia',
               '050' => 'Wisconsin',
               '051' => 'Wyoming',

               '052' => 'American Samoa',
               '053' => 'Federated States of Micronesia',
               '054' => 'Guam',
               '055' => 'Marshall Islands',
               '056' => 'Northern Mariana Islands',
               '057' => 'Palau',
               '058' => 'Puerto Rico',
               '059' => 'Virgin Islands'
              );
}
