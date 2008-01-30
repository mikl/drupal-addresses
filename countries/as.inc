<?php
// $Id$

// American Samoa

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
functionaddresses_province_list_as() {
  return array(
    'E' => t('Eastern'),
    'M' => t("Manu'a"),
    'R' => t('Rose Island'),
    'S' => t('Swains Island'),
    'W' => t('Western')
  );
}
