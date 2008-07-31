<?php
// $Id$

/**
 * @file
 * "Australia" specific data
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
 * states/provinces/teritories of a given contry
 *
 * @return
 *   Array. states where the keys are the state
 *   code and the value is the state name
 */
function addresses_province_list_au() {
  return array(
    'ACT' => t('Australian Capital Territory'),
    'NSW' => t('New South Wales'),
    'NT' => t('Northern Territory'),
    'QLD' => t('Queensland'),
    'SA' => t('South Australia'),
    'TAS' => t('Tasmania'),
    'VIC' => t('Victoria'),
    'WA' => t('Western Australia')
  );
}
