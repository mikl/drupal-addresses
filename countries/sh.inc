<?php
// $Id$

// Saint Helena

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
functionaddresses_province_list_sh() {
  return array(
    'A' => t('Ascension'),
    'S' => t('Saint Helena'),
    'T' => t('Tristan da Cunha')
  );
}
