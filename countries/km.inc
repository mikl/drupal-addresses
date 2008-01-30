<?php
// $Id$

// Comoros

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
functionaddresses_province_list_km() {
  return array(
    'G' => t('Grande Comore'),
    'A' => t('Anjouan'),
    'M' => t('Moheli')
  );
}
