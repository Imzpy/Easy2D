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
		int resNameId,				/* ������Դ���� */
		const String& resType		/* ������Դ���� */
	);

	virtual ~Music();

	// �������ļ�
	bool open(
		const e2d::String& filePath	/* �����ļ�·�� */
	);

	// ��������Դ
	bool open(
		int resNameId,				/* ������Դ���� */
		const String& resType		/* ������Դ���� */
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
	typedef std::map<UINT, Music*> MusicMap;

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
		int resNameId,			/* ������Դ���� */
		const String& resType	/* ������Դ���� */
	);

	// ��������
	bool play(
		int resNameId,			/* ������Դ���� */
		const String& resType,	/* ������Դ���� */
		int nLoopCount = 0		/* �ظ����Ŵ��������� -1 Ϊѭ������ */
	);

	// ��ͣ����
	void pause(
		int resNameId,			/* ������Դ���� */
		const String& resType	/* ������Դ���� */
	);

	// ������������
	void resume(
		int resNameId,			/* ������Դ���� */
		const String& resType	/* ������Դ���� */
	);

	// ֹͣ����
	void stop(
		int resNameId,			/* ������Դ���� */
		const String& resType	/* ������Դ���� */
	);

	// ��ȡ���ֲ���״̬
	bool isPlaying(
		int resNameId,			/* ������Դ���� */
		const String& resType	/* ������Դ���� */
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
	MusicMap				_fileList;
	MusicMap				_resList;
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


class Collision;

// ������
class Listener :
	public Ref
{
	friend class Input;
	friend class Collision;

public:
	Listener();

	explicit Listener(
		const Function& func,
		const String& name,
		bool paused
	);

	// ��������
	void start();

	// ֹͣ����
	void stop();

	// ��ȡ����������״̬
	bool isRunning() const;

	// ��ȡ����
	String getName() const;

	// ��������
	void setName(
		const String& name
	);

	// ���ü����ص�����
	void setFunc(
		const Function& func
	);

protected:
	// ���¼�����״̬
	virtual void _update();

protected:
	bool _running;
	bool _stopped;
	String _name;
	Function _callback;
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


// ·������
class Path
{
	friend class Game;

public:
	// �����Դ����·��
	static void addSearchPath(
		String path
	);

	// �����ļ�·��
	static String findFile(
		const String& path
	);

	// ��ȡ��Դ�ļ���������ȡ����ļ�·��
	static String extractResource(
		int resNameId,				/* ��Դ���� */
		const String& resType,		/* ��Դ���� */
		const String& destFileName	/* Ŀ���ļ��� */
	);

	// ��ȡ���ݵ�Ĭ�ϱ���·��
	static String getDataPath();

	// ��ȡ��ʱ�ļ�Ŀ¼
	static String getTempPath();

	// ��ȡ LocalAppData Ŀ¼
	static String getLocalAppDataPath();

	// ��ȡ��ǰ���������·��
	static String getCurrentFilePath();

	// ��ȡ�ļ���չ��
	static String getFileExtension(
		const String& filePath
	);

	// �򿪱����ļ��Ի���
	static String getSaveFilePath(
		const String& title = L"���浽",		/* �Ի������ */
		const String& defExt = L""			/* Ĭ����չ�� */
	);

	// �����ļ���
	static bool createFolder(
		const String& dirPath	/* �ļ���·�� */
	);

	// �ж��ļ����ļ����Ƿ����
	static bool exists(
		const String& dirPath	/* �ļ���·�� */
	);

private:
	static String _tempPath;
	static String _dataPath;
	static std::list<String> _paths;
};

}