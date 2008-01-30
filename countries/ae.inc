<?php
// $Id$

// United Arab Emirates

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
functionaddresses_province_list_ae() {
  return array(
    'AZ' => t('Abu Zaby'),
    'AJ' => t("'Ajman"),
    'FU' => t('Al Fujayrah'),
    'SH' => t('Ash Shariqah'),
    'DU' => t('Dubayy'),
    'RK' => t("R'as al Khaymah"),
    'UQ' => t('Umm al Qaywayn')
  );
}
