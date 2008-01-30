<?php
// $Id$

// Fiji

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
functionaddresses_province_list_fj() {
  return array(
    'C' => t('Central Division'),
    'N' => t('Northern Division'),
    'E' => t('Eastern Division'),
    'W' => t('Western Division'),
    'R' => t('Rotuma')
  );
}
