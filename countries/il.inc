<?php
// $Id$

// Israel

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
functionaddresses_province_list_il() {
  return array(
    'C' => t('Central'),
    'H' => t('Haifa'),
    'J' => t('Jerusalem'),
    'N' => t('Northern'),
    'S' => t('Southern'),
    'T' => t('Tel Aviv')
  );
}
