<?php
// $Id$

// Saint Pierre and Miquelon

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
functionaddresses_province_list_pm() {
  return array(
    'P' => t('Saint Pierre'),
    'M' => t('Miquelon')
  );
}
