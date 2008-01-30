<?php
// $Id$

// Andorra

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
function addresses_province_list_ad() {
  return array(
    'ALV' => t('Andorra la Vella'),
    'CAN' => t('Canillo'),
    'ENC' => t('Encamp'),
    'ESE' => t('Escaldes-Engordany'),
    'LMA' => t('La Massana'),
    'ORD' => t('Ordino'),
    'SJL' => t('Sant Julia de L�ria')
  );
}
