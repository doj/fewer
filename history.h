/* -*- mode: C++; c-basic-offset: 4; tab-width: 8; -*-
 * vi: set shiftwidth=4 tabstop=8:
 * :indentSize=4:tabSize=8:
 */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class History : public std::enable_shared_from_this<History>
{
#if defined(_WIN32)
private:
    std::wstring filename_;
public:
    const std::wstring& filename() const { return filename_; }
#else
private:
    std::string filename_;
public:
    const std::string& filename() const { return filename_; }
#endif

private:
    std::vector<std::string> v_;

    void load(std::istream& is);

    template <typename Str>
    void loadhistory(const Str& filename)
    {
	if (filename.empty()) {
	    return;
	}
	std::ifstream is(filename);
	load(is);
    }

public:
    History() {}
    explicit History(const std::string& filename);
    ~History();
    void add(const std::string& s);

    class iterator
    {
	std::shared_ptr<History> h_;
	const std::string s_;
	unsigned idx_;
    public:
	iterator(std::shared_ptr<History> h, const std::string& s);
	const std::string& next();
	const std::string& prev();
	bool atEnd() const;
    };
    friend class History::iterator;

    std::shared_ptr<iterator> begin(const std::string& s);

    typedef std::shared_ptr<History> ptr_t;
    typedef std::shared_ptr<History::iterator> iterator_t;
};
