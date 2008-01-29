<?php
// $Id$

// Australia

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
function address_province_list_au() {
  return array('ACT' => "Australian Capital Territory",
    'NSW' => "New South Wales",
    'NT' => "Northern Territory",
    'QLD' => "Queensland",
    'SA' => "South Australia",
    'TAS' => "Tasmania",
    'VIC' => "Victoria",
    'WA' => "Western Australia");
}
