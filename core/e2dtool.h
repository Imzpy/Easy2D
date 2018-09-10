#pragma once
#include "e2dutil.h"
#include "e2dimpl.h"

namespace e2d
{


	// �����������
	class Random
	{
	public:
		// ȡ�÷�Χ�ڵ�һ�����������
		template<typename T>
		static inline T Range(T min, T max)
		{
			return e2d::Random::RandomInt(min, max);
		}

		// ȡ�÷�Χ�ڵ�һ�������������
		static inline float Range(float min, float max)
		{
			return e2d::Random::RandomReal(min, max);
		}

		// ȡ�÷�Χ�ڵ�һ�������������
		static inline double Range(double min, double max)
		{
			return e2d::Random::RandomReal(min, max);
		}

	private:
		template<typename T>
		static T RandomInt(T min, T max)
		{
			std::uniform_int_distribution<T> dist(min, max);
			return dist(Random::GetEngine());
		}

		template<typename T>
		static T RandomReal(T min, T max)
		{
			std::uniform_real_distribution<T> dist(min, max);
			return dist(Random::GetEngine());
		}

		// ��ȡ�����������
		static std::default_random_engine &GetEngine();
	};


	// ����
	class Music :
		public Ref
	{
	public:
		Music();

		explicit Music(
			const e2d::String& file_path	/* �����ļ�·�� */
		);

		explicit Music(
			const Resource& res		/* ������Դ */
		);

		virtual ~Music();

		// �������ļ�
		bool Open(
			const e2d::String& file_path	/* �����ļ�·�� */
		);

		// ��������Դ
		bool Open(
			const Resource& res
		);

		// ����
		bool Play(
			int loopCount = 0
		);

		// ��ͣ
		void Pause();

		// ����
		void Resume();

		// ֹͣ
		void Stop();

		// �رղ�������Դ
		void Close();

		// �Ƿ����ڲ���
		bool IsPlaying() const;

		// ��������
		bool SetVolume(
			float volume
		);

		// ���ò��Ž���ʱ��ִ�к���
		void SetCallbackOnEnd(
			const Function& func
		);

		// ����ѭ��������ÿһ�β��Ž���ʱ��ִ�к���
		void SetCallbackOnLoopEnd(
			const Function& func
		);

		// ��ȡ IXAudio2SourceVoice ����
		IXAudio2SourceVoice * GetSourceVoice() const;

	protected:
		bool ReadMMIO();

		bool ResetFile();

		bool Read(
			BYTE* buffer,
			DWORD size_to_read
		);

		bool FindMediaFileCch(
			wchar_t* dest_path,
			int cch_dest,
			const wchar_t * file_name
		);

	protected:
		bool					opened_;
		DWORD					size_;
		CHAR*					buffer_;
		BYTE*					wave_data_;
		HMMIO					hmmio_;
		MMCKINFO				ck_;
		MMCKINFO				ck_riff_;
		WAVEFORMATEX*			wfx_;
		VoiceCallback			callback_;
		IXAudio2SourceVoice*	voice_;
	};


	// ���ֲ�����
	class Player
	{
	public:
		// ��ȡ������ʵ��
		static Player * GetInstance();

		// ����ʵ��
		static void DestroyInstance();

		// Ԥ����������Դ
		bool Preload(
			const String& file_path	/* �����ļ�·�� */
		);

		// ��������
		bool Play(
			const String& file_path,	/* �����ļ�·�� */
			int loop_count = 0		/* �ظ����Ŵ��������� -1 Ϊѭ������ */
		);

		// ��ͣ����
		void Pause(
			const String& file_path	/* �����ļ�·�� */
		);

		// ������������
		void Resume(
			const String& file_path	/* �����ļ�·�� */
		);

		// ֹͣ����
		void Stop(
			const String& file_path	/* �����ļ�·�� */
		);

		// ��ȡ���ֲ���״̬
		bool IsPlaying(
			const String& file_path	/* �����ļ�·�� */
		);

		// Ԥ����������Դ
		bool Preload(
			const Resource& res		/* ������Դ */
		);

		// ��������
		bool Play(
			const Resource& res,	/* ������Դ */
			int loop_count = 0		/* �ظ����Ŵ��������� -1 Ϊѭ������ */
		);

		// ��ͣ����
		void Pause(
			const Resource& res		/* ������Դ */
		);

		// ������������
		void Resume(
			const Resource& res		/* ������Դ */
		);

		// ֹͣ����
		void Stop(
			const Resource& res		/* ������Դ */
		);

		// ��ȡ���ֲ���״̬
		bool IsPlaying(
			const Resource& res		/* ������Դ */
		);

		// ��ȡ����
		float GetVolume();

		// ��������
		void SetVolume(
			float volume	/* ������ΧΪ -224 ~ 224��0 �Ǿ�����1 ���������� */
		);

		// ��ͣ��������
		void PauseAll();

		// ����������������
		void ResumeAll();

		// ֹͣ��������
		void StopAll();

		// ������ֻ���
		void ClearCache();

	protected:
		Player();

		~Player();

		E2D_DISABLE_COPY(Player);

	protected:
		float volume_;
		std::map<size_t, Music*> musics_;

		static Player * instance_;
	};


	// ���ݹ�����
	class Data
	{
	public:
		Data(
			const String& key,					/* ��ֵ */
			const String& field = L"Defalut"	/* �ֶ����� */
		);

		// �������Ƿ����
		bool Exists() const;

		// ���� int ���͵�ֵ
		bool SaveInt(
			int value
		);

		// ���� float ���͵�ֵ
		bool SaveFloat(
			float value
		);

		// ���� double ���͵�ֵ
		bool SaveDouble(
			double value
		);

		// ���� bool ���͵�ֵ
		bool SaveBool(
			bool value
		);

		// ���� String ���͵�ֵ
		bool SaveString(
			const String& value
		);

		// ��ȡ int ���͵�ֵ
		int GetInt() const;

		// ��ȡ float ���͵�ֵ
		float GetFloat() const;

		// ��ȡ double ���͵�ֵ
		double GetDouble() const;

		// ��ȡ bool ���͵�ֵ
		bool GetBool() const;

		// ��ȡ �ַ��� ���͵�ֵ
		String GetString();

	protected:
		String key_;
		String field_;
		const String& data_path_;
	};


	// �ļ�
	class File
	{
	public:
		File();

		File(
			const String& file_name
		);

		virtual ~File();

		// ���ļ�
		bool Open(
			const String& file_name
		);

		// �ļ����ļ����Ƿ����
		bool Exists() const;

		// �Ƿ����ļ���
		bool IsFolder() const;

		// ɾ���ļ�
		bool Delete();

		// ��ȡ�ļ�·��
		const String& GetPath() const;

		// ��ȡ�ļ���չ��
		String GetExtension() const;

		// �ͷ���Դ����ʱ�ļ�Ŀ¼
		static File Extract(
			int resource_name,				/* ��Դ���� */
			const String& resource_type,	/* ��Դ���� */
			const String& dest_file_name	/* Ŀ���ļ��� */
		);

		// ����ļ�����·��
		static void AddSearchPath(
			const String& path
		);

		// �����ļ���
		static bool CreateFolder(
			const String& dir_path	/* �ļ���·�� */
		);

		// �������ļ��Ի���
		static File ShowOpenDialog(
			const String& title = L"��",	/* �Ի������ */
			const String& filter = L""		/* ɸѡ��չ�������� "*.jpg;*.jpeg" */
		);

		// ���������ļ��Ի���
		static File ShowSaveDialog(
			const String& title = L"����",	/* �Ի������ */
			const String& def_file = L"",	/* Ĭ�ϱ�����ļ��� */
			const String& def_ext = L""		/* Ĭ��׷�ӵ���չ�������� "txt" */
		);

	protected:
		DWORD attributes_;
		String file_path_;

		static std::list<String> search_paths_;
	};


	// ·��
	class Path
	{
	public:
		// ��ȡ���ݵ�Ĭ�ϱ���·��
		static const String& GetDataPath();

		// ��ȡ��ʱ�ļ�Ŀ¼
		static const String& GetTemporaryPath();

		// ��ȡ LocalAppData Ŀ¼
		static const String& GetLocalAppDataPath();

		// ��ȡ��ǰ���������·��
		static const String& GetExeFilePath();
	};

}