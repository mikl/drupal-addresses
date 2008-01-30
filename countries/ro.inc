<?php
// $Id$

// Romania

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
function addresses_province_list_ro() {
  return array(
    'AL' => t('Alba'),
    'AD' => t('Arad'),
    'AG' => t('Arges'),
    'BA' => t('Bacau'),
    'BH' => t('Bihor'),
    'BN' => t('Bistrita-Nasaud'),
    'BO' => t('Botosani'),
    'BL' => t('Braila'),
    'BS' => t('Brasov'),
    'BC' => t('Bucuresti'),
    'BZ' => t('Buzau'),
    'CR' => t('Calarasi'),
    'CS' => t('Caras-Severin'),
    'CJ' => t('Cluj'),
    'CT' => t('Constanta'),
    'CV' => t('Covasna'),
    'DI' => t('Dimbovita'),
    'DO' => t('Dolj'),
    'GL' => t('Galati'),
    'GJ' => t('Gorj'),
    'GG' => t('Giurgiu'),
    'HA' => t('Harghita'),
    'HU' => t('Hunedoara'),
    'IM' => t('Ialomita'),
    'IS' => t('Iasi'),
    'IF' => t('Ilfov'),
    'MA' => t('Maramures'),
    'ME' => t('Mehedinti'),
    'MU' => t('Mures'),
    'NE' => t('Neamt'),
    'OL' => t('Olt'),
    'PR' => t('Prahova'),
    'SJ' => t('Salaj'),
    'SM' => t('Satu Mare'),
    'SO' => t('Sibiu'),
    'SU' => t('Suceava'),
    'TE' => t('Teleorman'),
    'SI' => t('Timis'),
    'TU' => t('Tulcea'),
    'VA' => t('Vaslui'),
    'VI' => t('Vilcea'),
    'VR' => t('Vrancea')
  );
}
