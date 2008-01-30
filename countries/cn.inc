<?php
// $Id$

// China

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
functionaddresses_province_list_cn() {
  return array(
    '11' => t('Beijing'),
    '12' => t('Tianjin'),
    '13' => t('Hebei'),
    '14' => t('Shanxi'),
    '15' => t('Nei Mongol'),
    '21' => t('Liaoning'),
    '22' => t('Jilin'),
    '23' => t('Heilongjiang'),
    '31' => t('Shanghai'),
    '32' => t('Jiangsu'),
    '33' => t('Zhejiang'),
    '34' => t('Anhui'),
    '35' => t('Fujian'),
    '36' => t('Jiangxi'),
    '37' => t('Shandong'),
    '41' => t('Henan'),
    '42' => t('Hubei'),
    '43' => t('Hunan'),
    '44' => t('Guangdong'),
    '45' => t('Guangxi'),
    '46' => t('Hainan'),
    '51' => t('Sichuan'),
    '52' => t('Guizhou'),
    '53' => t('Yunnan'),
    '54' => t('Xizang Z�zh�qu (Tibet)'),
    '61' => t('Shaanxi'),
    '62' => t('Gansu'),
    '63' => t('Qinghai'),
    '64' => t('Ningxia'),
    '65' => t('Xinjiang'),
    '71' => t('Taiwan'),
    '91' => t('Xianggang'),
    '92' => t('Aomen'),
    '97' => t('Chongq�ng'),
    '98' => t('Gaoxiong'),
    '99' => t('Taibei')
  );
}
