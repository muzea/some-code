<?php
/**
 * 用于更新DNS记录
 * 
 * Notice dns.json 格式如下
 * {
 *      "name": "需要更新的DNS记录",
 *      "zone_id": "",
 *      "record_id": "",
 *      "mail": "",
 *      "key": "",
 * }
 * 
 * @author  Mu Yu  <mr.muzea@gmail.com>
 * @license http://www.wtfpl.net/ WTFPL
 * 
 */
require 'vendor/autoload.php';

$jsonData = file_get_contents('dns.json');
$config = json_decode($jsonData, true);

$client = new GuzzleHttp\Client();
$ip = $_SERVER['remote_addr'];
$url = sprintf("https://api.cloudflare.com/client/v4/zones/%s/dns_records/%s", $config['zone_id'], $config['record_id']);
$header = [
    'X-Auth-Email' => $config['mail'],
    'X-Auth-Key' => $config['key'],
    'Content-Type' => 'application/json',
];
$formParams = [
    'type' => 'A',
    'name' => $config['name'],
    'content' => $ip,
];
$res = $client->request(
    'PUT', $url, [
        'headers' => $header,
        'body' => json_encode($formParams),
    ]
);

echo $res->getStatusCode();
