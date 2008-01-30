<?php
// $Id$

// Saint Vincent and the Grenadines

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
functionaddresses_province_list_vc() {
  return array(
    'C' => t('Charlotte'),
    'R' => t('Grenadines'),
    'A' => t('Saint Andrew'),
    'D' => t('Saint David'),
    'G' => t('Saint George'),
    'P' => t('Saint Patrick')
  );
}
