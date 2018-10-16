// Copyright (c) 2016-2018 Easy2D - Nomango
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include "e2dutil.h"
#include "e2dimpl.h"

namespace easy2d
{

	// �����������
	class Random
	{
	public:
		// ȡ�÷�Χ�ڵ�һ�����������
		template<typename T>
		static inline T Range(T min, T max)
		{
			return easy2d::Random::RandomInt(min, max);
		}

		// ȡ�÷�Χ�ڵ�һ�������������
		static inline float Range(float min, float max)
		{
			return easy2d::Random::RandomReal(min, max);
		}

		// ȡ�÷�Χ�ڵ�һ�������������
		static inline double Range(double min, double max)
		{
			return easy2d::Random::RandomReal(min, max);
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
	class Music
		: public Ref
	{
	public:
		Music();

		Music(
			const easy2d::String& file_path	/* �����ļ�·�� */
		);

		Music(
			const Resource& res				/* ������Դ */
		);

		virtual ~Music();

		// �������ļ�
		bool Load(
			const easy2d::String& file_path	/* �����ļ�·�� */
		);

		// ��������Դ
		bool Load(
			const Resource& res				/* ������Դ */
		);

		// ����
		bool Play(
			int loop_count = 0		/* ����ѭ������ (-1 Ϊѭ������) */
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

		// ��ȡ����
		float GetVolume() const;

		// ��������
		bool SetVolume(
			float volume	/* 1 Ϊԭʼ����, ���� 1 Ϊ�Ŵ�����, 0 Ϊ��С���� */
		);

		// ��ȡ IXAudio2SourceVoice ����
		IXAudio2SourceVoice * GetSourceVoice() const;

	protected:
		E2D_DISABLE_COPY(Music);

	protected:
		bool					opened_;
		bool					playing_;
		UINT32					size_;
		BYTE*					wave_data_;
		IXAudio2SourceVoice*	voice_;
	};


	// ���ֲ�����
	class Player
	{
	public:
		Player();

		~Player();

		// Ԥ����������Դ
		bool Load(
			const String& file_path	/* �����ļ�·�� */
		);

		// ��������
		bool Play(
			const String& file_path,	/* �����ļ�·�� */
			int loop_count = 0			/* ����ѭ������ (-1 Ϊѭ������) */
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
		bool Load(
			const Resource& res		/* ������Դ */
		);

		// ��������
		bool Play(
			const Resource& res,	/* ������Դ */
			int loop_count = 0		/* ����ѭ������ (-1 Ϊѭ������) */
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
		float GetVolume() const;

		// ��������
		void SetVolume(
			float volume			/* 1.0 Ϊԭʼ���� */
		);

		// ��ͣ��������
		void PauseAll();

		// ����������������
		void ResumeAll();

		// ֹͣ��������
		void StopAll();

		// �������
		static void ClearCache();

	protected:
		E2D_DISABLE_COPY(Player);

	protected:
		float volume_;

		static std::map<size_t, Music*> musics_;
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

		// �ļ��Ƿ����
		bool Exists() const;

		// ɾ���ļ�
		bool Delete();

		// ��ȡ�ļ�·��
		const String& GetPath() const;

		// ��ȡ�ļ���չ��
		String GetExtension() const;

		// �ͷ���Դ����ʱ�ļ�Ŀ¼
		static File Extract(
			const Resource& res,			/* ��Դ */
			const String& dest_file_name	/* Ŀ���ļ��� */
		);

		// ����ļ�����·��
		static void AddSearchPath(
			const String& path
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
		String	file_path_;

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