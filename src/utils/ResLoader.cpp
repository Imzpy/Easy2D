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

#include "ResLoader.h"
#include "../core/Image.h"
#include "../core/Frames.h"
#include "../core/modules.h"

namespace easy2d
{
	namespace
	{
		String Search(LPCWSTR file_name, List<String> const& paths)
		{
			for (const auto& path : paths)
			{
				if (modules::Shlwapi::Get().PathFileExistsW((path + file_name).c_str()))
				{
					return path + file_name;
				}
			}
			return file_name;
		}
	}

	void ResLoader::AddImage(String const& id, Resource const& image)
	{
		auto path = Search(image.GetFileName(), search_paths_);
		res_.insert(std::make_pair(id, SpImage(new Image(path.c_str()))));
	}

	void ResLoader::AddFrames(String const& id, Array<Resource> const& images, Duration const& interval)
	{
		auto frames = SpFrames(new Frames);
		frames->SetInterval(interval);

		for (const auto& image : images)
		{
			auto path = Search(image.GetFileName(), search_paths_);
			frames->Add(SpImage(new Image(path.c_str())));
		}
		res_.insert(std::make_pair(id, frames));
	}

	void ResLoader::AddObj(String const& id, SpObject const& obj)
	{
		res_.insert(std::make_pair(id, obj));
	}

	SpImage ResLoader::GetImage(String const & id) const
	{
		return Get<Image*>(id);
	}

	SpFrames ResLoader::GetFrames(String const & id) const
	{
		return Get<Frames*>(id);
	}

	SpObject ResLoader::GetObj(String const & id) const
	{
		return Get<Object*>(id);
	}

	void ResLoader::Delete(String const & id)
	{
		res_.erase(id);
	}

	void ResLoader::Destroy()
	{
		res_.clear();
	}

	void ResLoader::AddSearchPath(String const & path)
	{
		String tmp = path;
		size_t pos = 0;
		while ((pos = tmp.find(L"/", pos)) != String::npos)
		{
			tmp.replace(pos, 1, L"\\");
			pos++;
		}

		if (tmp.at(tmp.length() - 1) != L'\\')
		{
			tmp.append(L"\\");
		}

		auto iter = std::find(search_paths_.cbegin(), search_paths_.cend(), tmp);
		if (iter == search_paths_.cend())
		{
			search_paths_.push_front(tmp);
		}
	}

}