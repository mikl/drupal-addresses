<?php
// $Id$

// Tokelau

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
functionaddresses_province_list_tk() {
  return array(
    'A' => t('Atafu'),
    'F' => t('Fakaofo'),
    'N' => t('Nukunonu')
  );
}
