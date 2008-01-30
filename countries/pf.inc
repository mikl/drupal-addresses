<?php
// $Id$

// French Polynesia

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
function addresses_province_list_pf() {
  return array(
    'M' => t('Archipel des Marquises'),
    'T' => t('Archipel des Tuamotu'),
    'I' => t('Archipel des Tubuai'),
    'V' => t('Iles du Vent'),
    'S' => t('Iles Sous-le-Vent')
  );
}
