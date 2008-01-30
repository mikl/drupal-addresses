<?php
// $Id$

// Saint Lucia

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
functionaddresses_province_list_lc() {
  return array(
    'AR' => t('Anse-la-Raye'),
    'CA' => t('Castries'),
    'CH' => t('Choiseul'),
    'DA' => t('Dauphin'),
    'DE' => t('Dennery'),
    'GI' => t('Gros-Islet'),
    'LA' => t('Laborie'),
    'MI' => t('Micoud'),
    'PR' => t('Praslin'),
    'SO' => t('Soufriere'),
    'VF' => t('Vieux-Fort')
  );
}
