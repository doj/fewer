/* -*- mode: C++; c-basic-offset: 4; tab-width: 8; -*-
 * vi: set shiftwidth=4 tabstop=8:
 * :indentSize=4:tabSize=8:
 */

#pragma once
#include "types.h"
#include <vector>
#include <string>
#include <memory>

class file_index;

class DisplayInfo
{
    typedef lineNum_vector_t displayedLineNum_t;

    displayedLineNum_t displayedLineNum;
    displayedLineNum_t::iterator topLineIt;
    displayedLineNum_t::iterator bottomLineIt;

public:

    typedef std::shared_ptr<DisplayInfo> ptr_t;

    DisplayInfo();

    void assign(lineNum_vector_t&& v);

    /// @return the number of lines managed by this object.
    unsigned size() const { return displayedLineNum.size(); }

    /**
     * start an iteration over the lines.
     * This function can only be called after assign() has been called.
     * @return true if there are lines to display; false if there is nothing to display.
     */
    bool start();

    /**
     * get the current line number.
     * This function can only be called after start() has been called.
     * @return the current line number; 0 if the current line number is not valid.
     */
    line_number_t current() const;

    /**
     * advance to the next line.
     * This function can only be called after start() has been called.
     * @return true if there is a next line; false if the current line is the last line and nothing was advanced.
     */
    bool next();

    /**
     * advance to the previous line.
     * This function can only be called after start() has been called.
     * @return true if there is a previous line; false if the current line is the first line and nothing was advanced.
     */
    bool prev();

    /**
     * This function can only be called after start() has been called.
     * @return the line number of the top line on the display; 0 if nothing is displayed.
     */
    line_number_t topLineNum() const;

    /**
     * This function can only be called after start() has been called.
     * @return the line number of the bottom line on the display; 0 if nothing is displayed.
     */
    line_number_t bottomLineNum() const;

    /**
     * This function can only be called after assign() has been called.
     * @return the line number of the last line managed by this object; 0 if nothing is managed.
     */
    line_number_t lastLineNum() const;

    /**
     * position the object onto a line number.
     * This function can only be called after assign() has been called.
     * @return true if the line number is managed by this object; false if the line was not found.
     */
    bool go_to(const line_number_t lineNum);

    /**
     * position the object on line_num.
     * This function can only be called after assign() has been called.
     * If line_num is not included in the object, position on the previous line.
     */
    void go_to_approx(const line_number_t line_num);

    /**
     * position the object onto a line number approximately p percent into the lines.
     * @param p percentage, between [0..100].
     */
    void go_to_perc(unsigned p);

    /**
     * check if the first line is displayed.
     * This function can only be called after start() has been called.
     * @return true if the first line of the file is displayed.
     */
    bool isFirstLineDisplayed() const;

    /**
     * check if the last line is displayed.
     * This function can only be called after start() has been called.
     * @return true if the first line of the file is displayed.
     */
    bool isLastLineDisplayed() const;

    /**
     * move the display down one line.
     * This function can only be called after start() has been called.
     */
    void down();

    /**
     * move the display up one line.
     * This function can only be called after start() has been called.
     */
    void up();

    /// move the display to the first line.
    void top();

    /**
     * move the display down one page.
     * The old bottom line becomes the new top line.
     * This function can only be called after start() has been called.
     */
    void page_down();

    std::string info() const;

    /**
     * save the lines from fi to filename.
     * @param filename a file name. The file is created if it does not exist.
     * @return true if filename could be created and all lines could be written;
     *         false if a file error happened or fi does not contain all lines handled by this.
     */
    bool save(const std::string& filename, file_index& fi);
};
