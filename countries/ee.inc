<?php
// $Id$

// Estonia

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
function addresses_province_list_ee() {
  return array(
    '37' => t('Harju County'),
    '39' => t('Hiiu County'),
    '44' => t('Ida-Viru County'),
    '49' => t('J�geva County'),
    '51' => t('JArva County'),
    '57' => t('LAAne County'),
    '59' => t('LAAne-Viru County'),
    '65' => t('P�lva County'),
    '67' => t('PArnu County'),
    '70' => t('Rapla County'),
    '74' => t('Saare County'),
    '78' => t('Tartu County'),
    '82' => t('Valga County'),
    '84' => t('Viljandi County'),
    '86' => t('V�ru County')
  );
}
