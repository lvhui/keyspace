<?php

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

// Try to load our extension if it's not already loaded.
if (!extension_loaded("keyspace_client")) {
  if (strtolower(substr(PHP_OS, 0, 3)) === 'win') {
    if (!dl('php_keyspace_client.dll')) return;
  } else {
    // PHP_SHLIB_SUFFIX is available as of PHP 4.3.0, for older PHP assume 'so'.
    // It gives 'dylib' on MacOS X which is for libraries, modules are 'so'.
    if (PHP_SHLIB_SUFFIX === 'PHP_SHLIB_SUFFIX' || PHP_SHLIB_SUFFIX === 'dylib') {
      if (!dl('keyspace_client.so')) return;
    } else {
      if (!dl('keyspace_client.'.PHP_SHLIB_SUFFIX)) return;
    }
  }
}



abstract class keyspace_client {
	static function imaxabs($n) {
		return imaxabs($n);
	}

	static function imaxdiv($numer,$denom) {
		$r=imaxdiv($numer,$denom);
		return is_resource($r) ? new imaxdiv_t($r) : $r;
	}

	static function strtoimax($nptr,$endptr,$base) {
		return strtoimax($nptr,$endptr,$base);
	}

	static function strtoumax($nptr,$endptr,$base) {
		return strtoumax($nptr,$endptr,$base);
	}

	static function Keyspace_ResultBegin($result) {
		Keyspace_ResultBegin($result);
	}

	static function Keyspace_ResultNext($result) {
		Keyspace_ResultNext($result);
	}

	static function Keyspace_ResultIsEnd($result) {
		return Keyspace_ResultIsEnd($result);
	}

	static function Keyspace_ResultClose($result) {
		Keyspace_ResultClose($result);
	}

	static function Keyspace_ResultKey($result) {
		return Keyspace_ResultKey($result);
	}

	static function Keyspace_ResultValue($result) {
		return Keyspace_ResultValue($result);
	}

	static function Keyspace_ResultTransportStatus($result) {
		return Keyspace_ResultTransportStatus($result);
	}

	static function Keyspace_ResultConnectivityStatus($result) {
		return Keyspace_ResultConnectivityStatus($result);
	}

	static function Keyspace_ResultTimeoutStatus($result) {
		return Keyspace_ResultTimeoutStatus($result);
	}

	static function Keyspace_ResultCommandStatus($result) {
		return Keyspace_ResultCommandStatus($result);
	}

	static function Keyspace_Create() {
		return Keyspace_Create();
	}

	static function Keyspace_Init($client,$params) {
		return Keyspace_Init($client,$params);
	}

	static function Keyspace_Destroy($client) {
		Keyspace_Destroy($client);
	}

	static function Keyspace_GetResult($arg1) {
		return Keyspace_GetResult($arg1);
	}

	static function Keyspace_SetGlobalTimeout($client,$timeout) {
		Keyspace_SetGlobalTimeout($client,$timeout);
	}

	static function Keyspace_SetMasterTimeout($client,$timeout) {
		Keyspace_SetMasterTimeout($client,$timeout);
	}

	static function Keyspace_GetGlobalTimeout($client) {
		return Keyspace_GetGlobalTimeout($client);
	}

	static function Keyspace_GetMasterTimeout($client) {
		return Keyspace_GetMasterTimeout($client);
	}

	static function Keyspace_GetMaster($client) {
		return Keyspace_GetMaster($client);
	}

	static function Keyspace_DistributeDirty($client,$dd) {
		Keyspace_DistributeDirty($client,$dd);
	}

	static function Keyspace_Get($client,$key) {
		return Keyspace_Get($client,$key);
	}

	static function Keyspace_DirtyGet($client,$key) {
		return Keyspace_DirtyGet($client,$key);
	}

	static function Keyspace_Count($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_Count($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_CountStr($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_CountStr($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_DirtyCount($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_DirtyCount($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_DirtyCountStr($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_DirtyCountStr($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_ListKeys($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_ListKeys($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_ListKeysStr($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_ListKeysStr($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_DirtyListKeys($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_DirtyListKeys($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_DirtyListKeysStr($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_DirtyListKeysStr($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_ListKeyValues($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_ListKeyValues($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_ListKeyValuesStr($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_ListKeyValuesStr($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_DirtyListKeyValues($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_DirtyListKeyValues($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_DirtyListKeyValuesStr($client,$prefix,$startKey,$count,$next,$forward) {
		return Keyspace_DirtyListKeyValuesStr($client,$prefix,$startKey,$count,$next,$forward);
	}

	static function Keyspace_Set($client,$key,$value) {
		return Keyspace_Set($client,$key,$value);
	}

	static function Keyspace_TestAndSet($client,$key,$test,$value) {
		return Keyspace_TestAndSet($client,$key,$test,$value);
	}

	static function Keyspace_Add($client,$key,$num) {
		return Keyspace_Add($client,$key,$num);
	}

	static function Keyspace_AddStr($client,$key,$num) {
		return Keyspace_AddStr($client,$key,$num);
	}

	static function Keyspace_Delete($client,$key) {
		return Keyspace_Delete($client,$key);
	}

	static function Keyspace_Remove($client,$key) {
		return Keyspace_Remove($client,$key);
	}

	static function Keyspace_Rename($client,$from,$to) {
		return Keyspace_Rename($client,$from,$to);
	}

	static function Keyspace_Prune($client,$prefix) {
		return Keyspace_Prune($client,$prefix);
	}

	static function Keyspace_SetExpiry($client,$key,$exptime) {
		return Keyspace_SetExpiry($client,$key,$exptime);
	}

	static function Keyspace_RemoveExpiry($client,$key) {
		return Keyspace_RemoveExpiry($client,$key);
	}

	static function Keyspace_Begin($client) {
		return Keyspace_Begin($client);
	}

	static function Keyspace_Submit($client) {
		return Keyspace_Submit($client);
	}

	static function Keyspace_Cancel($client) {
		return Keyspace_Cancel($client);
	}

	static function Keyspace_IsBatched($client) {
		return Keyspace_IsBatched($client);
	}

	static function Keyspace_SetTrace($trace) {
		Keyspace_SetTrace($trace);
	}
}

/* PHP Proxy Classes */
class imaxdiv_t {
	public $_cPtr=null;

	function __set($var,$value) {
		if ($var == 'quot') return imaxdiv_t_quot_set($this->_cPtr,$value);
		if ($var == 'rem') return imaxdiv_t_rem_set($this->_cPtr,$value);
	}

	function __get($var) {
		if ($var == 'quot') return imaxdiv_t_quot_get($this->_cPtr);
		if ($var == 'rem') return imaxdiv_t_rem_get($this->_cPtr);
		return null;
	}

	function __construct() {
		$this->_cPtr=new_imaxdiv_t();
	}
}

class Keyspace_NodeParams {
	public $_cPtr=null;

	function __set($var,$value) {
		$func = 'Keyspace_NodeParams_'.$var.'_set';
		if (function_exists($func)) call_user_func($func,$this->_cPtr,$value);
	}

	function __get($var) {
		$func = 'Keyspace_NodeParams_'.$var.'_get';
		if (function_exists($func)) return call_user_func($func,$this->_cPtr);
		return null;
	}

	function __construct($nodec_) {
		$this->_cPtr=new_Keyspace_NodeParams($nodec_);
	}

	function Close() {
		Keyspace_NodeParams_Close($this->_cPtr);
	}

	function AddNode($node) {
		Keyspace_NodeParams_AddNode($this->_cPtr,$node);
	}
}


?>
