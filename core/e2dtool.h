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
	static inline double range(float min, float max) 
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
		const e2d::String& filePath	/* �����ļ�·�� */
	);

	explicit Music(
		const Resource& res
	);

	virtual ~Music();

	// �������ļ�
	bool open(
		const e2d::String& filePath	/* �����ļ�·�� */
	);

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
		double volume
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
	IXAudio2SourceVoice*	_voice;
};


// ���ֲ�����
class Player
{
	friend class Game;
	typedef std::map<Resource, Music*> MusicMap;

public:
	// ��ȡ������ʵ��
	static Player * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// Ԥ����������Դ
	bool preload(
		const String& filePath	/* �����ļ�·�� */
	);

	// ��������
	bool play(
		const String& filePath,	/* �����ļ�·�� */
		int nLoopCount = 0		/* �ظ����Ŵ��������� -1 Ϊѭ������ */
	);

	// ��ͣ����
	void pause(
		const String& filePath	/* �����ļ�·�� */
	);

	// ������������
	void resume(
		const String& filePath	/* �����ļ�·�� */
	);

	// ֹͣ����
	void stop(
		const String& filePath	/* �����ļ�·�� */
	);

	// ��ȡ���ֲ���״̬
	bool isPlaying(
		const String& filePath	/* �����ļ�·�� */
	);

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
	double getVolume();

	// ��������
	void setVolume(
		double volume			/* ������ΧΪ -224 ~ 224��0 �Ǿ�����1 ���������� */
	);

	// ��ͣ��������
	void pauseAll();

	// ����������������
	void resumeAll();

	// ֹͣ��������
	void stopAll();

	// ������ֻ���
	void clearCache();

	// ��ȡ IXAudio2 ����
	IXAudio2 * getXAudio2();

private:
	Player();

	~Player();

	E2D_DISABLE_COPY(Player);

private:
	float					_volume;
	MusicMap				_musicList;
	IXAudio2*				_xAudio2;
	IXAudio2MasteringVoice*	_masteringVoice;

	static Player * _instance;
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
		const String& name = L""	/* ��ʱ������ */
	);

	explicit Task(
		const Function& func,		/* ִ�к��� */
		double delay,				/* ʱ�������룩 */
		int times = -1,				/* ִ�д������� -1 Ϊ����ִ�У� */
		const String& name = L""	/* ��ʱ������ */
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
	double		_delay;
	double		_lastTime;
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

	// ����������ͬ���Ƶ�����
	void resumeTasks(
		const String& name
	);

	// ��ͣ������ͬ���Ƶ�����
	void pauseTasks(
		const String& name
	);

	// �Ƴ�������ͬ���Ƶ�����
	void removeTasks(
		const String& name
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
	// ���� int ���͵�ֵ
	static void saveInt(
		const String& key,					/* ��ֵ */
		int value,							/* ���� */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ���� double ���͵�ֵ
	static void saveDouble(
		const String& key,					/* ��ֵ */
		double value,						/* ���� */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ���� bool ���͵�ֵ
	static void saveBool(
		const String& key,					/* ��ֵ */
		bool value,							/* ���� */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ���� �ַ��� ���͵�ֵ
	static void saveString(
		const String& key,					/* ��ֵ */
		const String& value,				/* ���� */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ��ȡ int ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	static int getInt(
		const String& key,					/* ��ֵ */
		int defaultValue,					/* Ĭ��ֵ */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ��ȡ double ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	static double getDouble(
		const String& key,					/* ��ֵ */
		double defaultValue,				/* Ĭ��ֵ */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ��ȡ bool ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	static bool getBool(
		const String& key,					/* ��ֵ */
		bool defaultValue,					/* Ĭ��ֵ */
		const String& field = L"Defalut"	/* �ֶ����� */
	);

	// ��ȡ �ַ��� ���͵�ֵ
	// �����������򷵻� defaultValue ������ֵ��
	static String getString(
		const String& key,					/* ��ֵ */
		const String& defaultValue,			/* Ĭ��ֵ */
		const String& field = L"Defalut"	/* �ֶ����� */
	);
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