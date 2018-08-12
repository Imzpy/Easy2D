#pragma once
#include "e2dbase.h"

namespace e2d
{


// �����������
class Random
{
public:
	// ȡ�÷�Χ�ڵ�һ�����������
	template<typename T>
	static inline T range(T min, T max) 
	{ 
		return e2d::Random::__randomInt(min, max); 
	}

	// ȡ�÷�Χ�ڵ�һ�������������
	static inline float range(float min, float max) 
	{ 
		return e2d::Random::__randomReal(min, max); 
	}

	// ȡ�÷�Χ�ڵ�һ�������������
	static inline double range(double min, double max)
	{ 
		return e2d::Random::__randomReal(min, max); 
	}

private:
	template<typename T>
	static T __randomInt(T min, T max)
	{
		std::uniform_int_distribution<T> dist(min, max);
		return dist(Random::__getEngine());
	}

	template<typename T>
	static T __randomReal(T min, T max)
	{
		std::uniform_real_distribution<T> dist(min, max);
		return dist(Random::__getEngine());
	}

	// ��ȡ�����������
	static std::default_random_engine &__getEngine();
};


// ����
class Music :
	public Ref
{
	friend class VoiceCallback;

public:
	Music();

	explicit Music(
		const Resource& res		/* ������Դ */
	);

	explicit Music(
		IXAudio2* xAudio2
	);

	virtual ~Music();

	// ��������Դ
	bool open(
		const Resource& res
	);

	// ����
	bool play(
		int nLoopCount = 0
	);

	// ��ͣ
	void pause();

	// ����
	void resume();

	// ֹͣ
	void stop();

	// �رղ�������Դ
	void close();

	// �Ƿ����ڲ���
	bool isPlaying() const;

	// ��������
	bool setVolume(
		float volume
	);

	// ���ò��Ž���ʱ��ִ�к���
	void setFuncOnEnd(
		const Function& func
	);

	// ����ѭ��������ÿһ�β��Ž���ʱ��ִ�к���
	void setFuncOnLoopEnd(
		const Function& func
	);

	// ��ȡ IXAudio2SourceVoice ����
	IXAudio2SourceVoice * getIXAudio2SourceVoice() const;

protected:
	bool _readMMIO();

	bool _resetFile();

	bool _read(
		BYTE* pBuffer,
		DWORD dwSizeToRead
	);

	bool _findMediaFileCch(
		wchar_t* strDestPath,
		int cchDest,
		const wchar_t * strFilename
	);

protected:
	bool					_opened;
	bool					_playing;
	DWORD					_dwSize;
	CHAR*					_resBuffer;
	BYTE*					_waveData;
	HMMIO					_hmmio;
	MMCKINFO				_ck;
	MMCKINFO				_ckRiff;
	WAVEFORMATEX*			_wfx;
	VoiceCallback			_voiceCallback;
	IXAudio2*				_xAudio2;
	IXAudio2SourceVoice*	_voice;
	IXAudio2MasteringVoice*	_masteringVoice;
};


// ���ֲ�����
class Player
{
	friend class Game;

public:
	Player();

	~Player();

	// Ԥ����������Դ
	bool preload(
		const Resource& res		/* ������Դ */
	);

	// ��������
	bool play(
		const Resource& res,	/* ������Դ */
		int nLoopCount = 0		/* �ظ����Ŵ��������� -1 Ϊѭ������ */
	);

	// ��ͣ����
	void pause(
		const Resource& res		/* ������Դ */
	);

	// ������������
	void resume(
		const Resource& res		/* ������Դ */
	);

	// ֹͣ����
	void stop(
		const Resource& res		/* ������Դ */
	);

	// ��ȡ���ֲ���״̬
	bool isPlaying(
		const Resource& res		/* ������Դ */
	);

	// ��ȡ����
	float getVolume();

	// ��������
	void setVolume(
		float volume	/* ������ΧΪ -224 ~ 224��0 �Ǿ�����1 ���������� */
	);

	// ��ͣ��������
	void pauseAll();

	// ����������������
	void resumeAll();

	// ֹͣ��������
	void stopAll();

	// �򿪻�رղ�����
	void setEnabled(
		bool enabled
	);

	// ������ֻ���
	void clearCache();

	// ��ȡ XAudio2 ʵ������
	IXAudio2 * getXAudio2();

	// ��ȡ MasteringVoice ʵ������
	IXAudio2MasteringVoice* getMasteringVoice();

private:
	bool _enabled;
	float _volume;
	IXAudio2*					_xAudio2;
	IXAudio2MasteringVoice*		_masteringVoice;
	std::map<Resource, Music*>	_musicList;
};


class Timer;

// ��ʱ����
class Task :
	public Ref
{
	friend class Timer;

public:
	explicit Task(
		const Function& func,		/* ִ�к��� */
		const String& name = L""	/* �������� */
	);

	explicit Task(
		const Function& func,		/* ִ�к��� */
		float delay,				/* ʱ�������룩 */
		int times = -1,				/* ִ�д������� -1 Ϊ����ִ�У� */
		const String& name = L""	/* �������� */
	);

	// ��ͣ����
	void pause();

	// ��������
	void resume();

	// �����Ƿ����
	bool isReady() const;

	// �����Ƿ�����ִ��
	bool isRunning() const;

	// ��ȡ��������
	String getName() const;

	// ִ������
	void update();

	// ˢ�������ʱ
	void updateTime();

private:
	bool		_running;
	bool		_stopped;
	int			_runTimes;
	int			_totalTimes;
	Duration	_delay;
	Time		_lastTime;
	String		_name;
	Function	_callback;
};


// ��ʱ��
class Timer
{
public:
	// ��ȡ��ʱ��ʵ��
	static Timer * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// �������
	void addTask(
		Task * task
	);

	// ��������
	void resumeTasks(
		const String& taskName
	);

	// ��ͣ����
	void pauseTasks(
		const String& taskName
	);

	// �Ƴ�����
	void removeTasks(
		const String& taskName
	);

	// ������������
	void resumeAllTasks();

	// ��ͣ��������
	void pauseAllTasks();

	// �Ƴ���������
	void removeAllTasks();

	// ǿ�������������
	void clearAllTasks();

	// ���¶�ʱ��
	void update();

	// ˢ�����������ʱ
	void updateTime();

private:
	Timer();

	~Timer();

	E2D_DISABLE_COPY(Timer);

private:
	std::vector<Task*> _tasks;

	static Timer * _instance;
};


// ���ݹ�����
class Data
{
public:
	Data(
		const String& key,					/* ��ֵ */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ���� int ���͵�ֵ
	void saveInt(
		int value							/* ���� */
	);

	// ���� float ���͵�ֵ
	void saveDouble(
		float value						/* ���� */
	);

	// ���� bool ���͵�ֵ
	void saveBool(
		bool value							/* ���� */
	);

	// ���� �ַ��� ���͵�ֵ
	void saveString(
		const String& value				/* ���� */
	);

	// ��ȡ int ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	int getInt(
		int defaultValue					/* Ĭ��ֵ */
	);

	// ��ȡ float ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	float getDouble(
		float defaultValue				/* Ĭ��ֵ */
	);

	// ��ȡ bool ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	bool getBool(
		bool defaultValue					/* Ĭ��ֵ */
	);

	// ��ȡ �ַ��� ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	String getString(
		const String& defaultValue			/* Ĭ��ֵ */
	);

protected:
	String _key;
	String _field;
	const String _dataPath;
};


// �ļ�
class File
{
public:
	File();

	File(
		const String& fileName
	);

	virtual ~File();

	// ���ļ�
	bool open(
		const String& fileName
	);

	// �ļ����ļ����Ƿ����
	bool exists() const;

	// �Ƿ����ļ���
	bool isFolder() const;

	// ɾ���ļ�
	bool deleteFile();

	// ��ȡ�ļ�·��
	String getFilePath() const;

	// ��ȡ�ļ���չ��
	String getExtension() const;

	// �ͷ���Դ����ʱ�ļ�Ŀ¼
	static File extract(
		int resNameId,				/* ��Դ���� */
		const String& resType,		/* ��Դ���� */
		const String& destFileName	/* Ŀ���ļ��� */
	);

	// ����ļ�����·��
	static void addSearchPath(
		const String& path
	);

	// �����ļ���
	static bool createFolder(
		const String& dirPath	/* �ļ���·�� */
	);

	// �򿪱����ļ��Ի���
	static String getSaveFilePath(
		const String& title = L"���浽",		/* �Ի������ */
		const String& defExt = L""			/* Ĭ����չ�� */
	);

protected:
	DWORD _attributes;
	String _fileName;

	static std::list<String> _searchPaths;
};


// ·��
class Path
{
	friend class Game;

public:
	// ��ȡ���ݵ�Ĭ�ϱ���·��
	static String getDataPath();

	// ��ȡ��ʱ�ļ�Ŀ¼
	static String getTempPath();

	// ��ȡ LocalAppData Ŀ¼
	static String getLocalAppDataPath();

	// ��ȡ��ǰ���������·��
	static String getCurrentFilePath();
};

}