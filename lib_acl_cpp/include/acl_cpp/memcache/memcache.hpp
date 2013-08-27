#pragma once
#include "acl_cpp/acl_cpp_define.hpp"
#include <time.h>
#include "acl_cpp/connpool/connect_client.hpp"
#include "acl_cpp/stdlib/string.hpp"
#include "acl_cpp/mime/rfc2047.hpp"

namespace acl {

class socket_stream;

typedef class memcache mem_cache;

/**
 * memcached �ͻ���ͨ��Э��⣬֧�ֳ��������Զ�����
 */
class ACL_CPP_API memcache : public connect_client
{
public:
	/**
	* ���캯��
	* @param addr {const char*} memcached ������������ַ����ʽΪ��
	*  ip:port����: 127.0.0.1:11211
	* @param conn_timeout {int} ���ӳ�ʱʱ��(��)
	* @param rw_timeout {int} IO ��д��ʱʱ��(��)
	*/
	memcache(const char* addr = "127.0.0.1:11211",
		int conn_timeout = 180, int rw_timeout = 300);

	~memcache();

	/**
	 * ���� key ��ǰ׺����ʵ�ʵ� key ���� ��ǰ׺+ԭʼkey ��ɣ�ȱʡʱ����ǰ׺��
	 * �����Ӧ�ù���ͬһ�� memcached ����ʱ������Ӧ������������ key ǰ׺������
	 * ���Ա���������Ӧ�õ� key �����ظ�����
	 * @param keypre {const char*} �ǿ�ʱ���� key ǰ׺������ȡ�� key ǰ׺
	 * @return {memcache&}
	 */
	memcache& set_prefix(const char* keypre);

	/**
	 * �ڱ��ֵĳ������ж�ʱ�Ƿ�Ҫ���Զ�������ȱʡΪ�Զ�����
	 * @param onoff {bool} Ϊ true ʱ��ʾ����������Ͽ����Զ�����
	 * @return {memcache&}
	 */
	memcache& auto_retry(bool onoff);

	/**
	 * �����Ƿ���� KEY ��ֵ���б��룬ȱ��ʱ���� key ���룬��Ӧ�õ� key �п���
	 * ���������ַ��������ֵʱ��������ô˺����� key ���б���
	 * @parma onoff {bool} Ϊ true ��ʾ�ڲ���Ҫ�� key ���б���
	 * @return {memcache&}
	 */
	memcache& encode_key(bool onoff);

	/**
	* �� memcached ���޸Ļ������µ����ݻ������
	* @param key {const char*} ��ֵ
	* @param klen {size_t} key ��ֵ����
	* @param dat {const void*} ����
	* @param dlen {size_t} data ���ݳ���
	* @param timeout {time_t} ���泬ʱʱ��(��)
	* @param flags {unsigned short} �����ı�־λ
	* @return {bool} �Ƿ�ɹ�
	*/
	bool set(const char* key, size_t klen,
		const void* dat, size_t dlen,
		time_t timeout = 0, unsigned short flags = 0);

	/**
	* �� memcached ���޸Ļ������µ����ݻ������
	* @param key {const char*} �ַ�����ֵ
	* @param dat {const void*} ����
	* @param dlen {size_t} data ���ݳ���
	* @param timeout {time_t} ���泬ʱʱ��(��)
	* @param flags {unsigned short} �����ı�־λ
	* @return {bool} �Ƿ�ɹ�
	*/
	bool set(const char* key, const void* dat, size_t dlen,
		time_t timeout = 0, unsigned short flags = 0);

	/**
	* ���� memcached ���Ѿ����ڵļ��Ĺ������ڣ���ΪĿǰ libmemcached û��
	* �ṩ�˽ӿڣ����Ըú���ʵ�ֵķ�ʽ���ȵ��� get ȡ����Ӧ����ֵ��Ȼ����
	* ���� set �������øü���ֵ������ʱ��
	* @param key {const char*} ��ֵ
	* @param klen {size_t} key ��ֵ����
	* @param timeout {time_t} ����ʱ��(��)
	* @return {bool} �Ƿ�ɹ�
	*/
	bool set(const char* key, size_t klen, time_t timeout = 0);

	/**
	* ���� memcached ���Ѿ����ڵļ��Ĺ������ڣ���ΪĿǰ libmemcached û��
	* �ṩ�˽ӿڣ����Ըú���ʵ�ֵķ�ʽ���ȵ��� get ȡ����Ӧ����ֵ��Ȼ����
	* ���� set �������øü���ֵ������ʱ��
	* @param key {const char*} �ַ�����ֵ
	* @param timeout {time_t} ����ʱ��(��)
	* @return {bool} �Ƿ�ɹ�
	*/
	bool set(const char* key, time_t timeout = 0);

	/**
	* �� memcached �л�ö�Ӧ��ֵ�Ļ�������
	* @param key {const char*} �ַ�����ֵ
	* @param klen {size_t} ��ֵ����
	* @param buf {string&} �洢����Ļ��������ڲ����Ȼ���ոû�����
	* @param flags {unsigned short*} �洢�����ı�־λ
	* @return {bool} ���� true ��ʾ��ȷ��ý��ֵ�������ʾ��ֵ��Ӧ��
	*  ���ݲ����ڻ����
	*/
	bool get(const char* key, size_t klen, string& buf,
		unsigned short* flags = NULL);

	/**
	* �� memcached �л�ö�Ӧ��ֵ�Ļ�������
	* @param key {const char*} �ַ�����ֵ
	* @param buf {string&} �洢����Ļ��������ڲ����Ȼ���ոû�����
	* @param flags {unsigned short*} �洢�����ı�־λ
	* @return {bool} ���� true ��ʾ��ȷ��ý��ֵ�������ʾ��ֵ��Ӧ��
	*  ���ݲ����ڻ����
	*/
	bool get(const char* key, string& buf, unsigned short* flags = NULL);

	/**
	* �� memcached ��ɾ������
	* @param key {const char*} ��ֵ
	* @param klen {size_t} ��ֵ����
	* @return {bool} ɾ���Ƿ�ɹ�
	*/
	bool del(const char* key, size_t klen);

	/**
	* �� memcached ��ɾ������
	* @param key {const char*} �ַ�����ֵ
	* @return {bool} ɾ���Ƿ�ɹ�
	*/
	bool del(const char* key);

	/**
	* ����ϴβ��� memcached ����������Ϣ
	* @return {const char*} ����������Ϣ������Ϊ��
	*/
	const char* last_serror() const;

	/**
	* ����ϴβ��� memcached �Ĵ����
	* @return {int} �����
	*/
	int  last_error() const;

	/**
	* ���� memcached ������, ��Ϊ set/get/del ���������Զ�����
	* memcached �����ӣ����Բ�����ʾ�ص��ô˺��������� memcached
	* ������
	* @return {bool} ���Ƿ�ɹ�
	*/
	virtual bool open();

	/**
	* �ر��� memcached �����ӣ�һ��ú�������Ҫ���ã���Ϊ�������
	* ����ʱ���Զ����ô˺���
	*/
	void close();

	/**
	* �г� memcached ���ӵ�һЩ���ԣ�������
	*/
	void property_list();

private:
	bool set(const string& key, const void* dat, size_t dlen,
		time_t timeout, unsigned short flags);
	bool get(const string& key, string& buf, unsigned short* flags);
	const string& get_key(const char* key, size_t klen);

	string* keypre_;
	rfc2047 coder_;
	int   conn_timeout_;
	int   rw_timeout_;
	bool  encode_key_;

	bool  opened_;
	bool  retry_;
	char* addr_;
	char* ip_;
	int   port_;
	int   enum_;
	string ebuf_;
	string kbuf_;

	socket_stream* conn_;
	string req_line_;
	string res_line_;
	bool error_happen(const char* line);
};

} // namespace acl