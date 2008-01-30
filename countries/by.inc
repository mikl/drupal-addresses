<?php
// $Id$

// Belarus

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
functionaddresses_province_list_by() {
  return array(
    'BR' => t('Brest voblast'),
    'HO' => t('Homyel voblast'),
    'HR' => t('Hrodna voblast'),
    'MA' => t('Mahilyow voblast'),
    'MI' => t('Minsk voblast'),
    'VI' => t('Vitsebsk voblast')
  );
}
