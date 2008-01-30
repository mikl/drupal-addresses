<?php
// $Id$

// Cameroon

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
function addresses_province_list_cm() {
  return array(
    'ADA' => t('Adamawa Province (Adamaoua)'),
    'CEN' => t('Centre Province'),
    'EST' => t('East Province (Est)'),
    'EXN' => t('Extreme North Province (Extr�me-Nord)'),
    'LIT' => t('Littoral Province'),
    'NOR' => t('North Province (Nord)'),
    'NOT' => t('Northwest Province (Nord-Ouest)'),
    'OUE' => t('West Province (Ouest)'),
    'SUD' => t('South Province (Sud)'),
    'SOU' => t('Southwest Province (Sud-Ouest).')
  );
}
