<?php
// $Id$

// Norway

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
functionaddresses_province_list_no() {
  return array(
    'AK' => t('Akershus'),
    'AA' => t('Aust-Agder'),
    'BU' => t('Buskerud'),
    'FM' => t('Finnmark'),
    'HM' => t('Hedmark'),
    'HL' => t('Hordaland'),
    'MR' => t('More og Romdal'),
    'NL' => t('Nordland'),
    'NT' => t('Nord-Trondelag'),
    'OP' => t('Oppland'),
    'OL' => t('Oslo'),
    'OF' => t('Ostfold'),
    'RL' => t('Rogaland'),
    'SJ' => t('Sogn og Fjordane'),
    'ST' => t('Sor-Trondelag'),
    'TM' => t('Telemark'),
    'TR' => t('Troms'),
    'VA' => t('Vest-Agder'),
    'VF' => t('Vestfold')
  );
}
