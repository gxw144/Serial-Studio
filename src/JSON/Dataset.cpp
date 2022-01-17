/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <JSON/Dataset.h>
#include <JSON/Generator.h>

JSON::Dataset::Dataset()
    : m_fft(false)
    , m_led(false)
    , m_log(false)
    , m_graph(false)
    , m_title("")
    , m_value("")
    , m_units("")
    , m_widget("")
    , m_index(0)
    , m_max(0)
    , m_min(0)
    , m_alarm(0)
    , m_fftSamples(1024)
{
}

/**
 * @return @c true if the UI should generate a FFT plot of this dataset
 */
bool JSON::Dataset::fft() const
{
    return m_fft;
}

/**
 * @return @c true if the UI should generate a LED of this dataset
 */
bool JSON::Dataset::led() const
{
    return m_led;
}

/**
 * @return @c true if the UI should generate a logarithmic plot of this dataset
 */
bool JSON::Dataset::log() const
{
    return m_log;
}

/**
 * @return the field index represented by the current dataset
 */
int JSON::Dataset::index() const
{
    return m_index;
}

/**
 * @return @c true if the UI should graph this dataset
 */
bool JSON::Dataset::graph() const
{
    return m_graph;
}

/**
 * Returns the minimum value of the dataset
 */
double JSON::Dataset::min() const
{
    return m_min;
}

/**
 * Returns the maximum value of the dataset
 */
double JSON::Dataset::max() const
{
    return m_max;
}

/**
 * Returns the alarm level of the dataset
 */
double JSON::Dataset::alarm() const
{
    return m_alarm;
}

/**
 * @return The title/description of this dataset
 */
QString JSON::Dataset::title() const
{
    return m_title;
}

/**
 * @return The value/reading of this dataset
 */
QString JSON::Dataset::value() const
{
    return m_value;
}

/**
 * @return The units of this dataset
 */
QString JSON::Dataset::units() const
{
    return m_units;
}

/**
 * @return The widget value of this dataset
 */
QString JSON::Dataset::widget() const
{
    return m_widget;
}

/**
 * Returns the maximum freq. for the FFT transform
 */
int JSON::Dataset::fftSamples() const
{
    return qMax(1, m_fftSamples);
}

/**
 * Returns the JSON data that represents this widget
 */
QJsonObject JSON::Dataset::jsonData() const
{
    return m_jsonData;
}

/**
 * Reads dataset information from the given @a object and evaluates any JS code in the
 * "value" field of the dataset.
 *
 * @return @c true on read success, @c false on failure
 */
bool JSON::Dataset::read(const QJsonObject &object)
{
    if (!object.isEmpty())
    {
        m_fft = object.value("fft").toBool();
        m_led = object.value("led").toBool();
        m_log = object.value("log").toBool();
        m_min = object.value("min").toDouble();
        m_max = object.value("max").toDouble();
        m_index = object.value("index").toInt();
        m_alarm = object.value("alarm").toDouble();
        m_graph = object.value("graph").toBool();
        m_title = object.value("title").toString();
        m_value = object.value("value").toString();
        m_units = object.value("units").toString();
        m_widget = object.value("widget").toString();
        m_fftSamples = object.value("fftSamples").toInt();

        if (m_value.isEmpty())
            m_value = "--.--";

        return true;
    }

    return false;
}
