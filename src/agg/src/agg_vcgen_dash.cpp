//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.4
// Copyright (C) 2002-2005 Maxim Shemanarev (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------
//
// Line dash generator
//
//----------------------------------------------------------------------------

#include <cmath>
#include "agg_vcgen_dash.h"
#include "agg_shorten_path.h"

namespace agg
{

    //------------------------------------------------------------------------
    vcgen_dash::vcgen_dash() :
        m_total_dash_len(0.0),
        m_num_dashes(0),
        m_dash_start(0.0),
        m_shorten(0.0),
        m_curr_dash_start(0.0),
        m_curr_dash(0),
        m_src_vertices(),
        m_closed(0),
        m_status(initial),
        m_src_vertex(0)
    {
    }



    //------------------------------------------------------------------------
    void vcgen_dash::remove_all_dashes()
    {
        m_total_dash_len = 0.0;
        m_num_dashes = 0;
        m_curr_dash_start = 0.0;
        m_curr_dash = 0;
    }


    //------------------------------------------------------------------------
    void vcgen_dash::add_dash(double dash_len, double gap_len)
    {
        if(m_num_dashes < max_dashes)
        {
            m_total_dash_len += dash_len + gap_len;
            m_dashes[m_num_dashes++] = dash_len;
            m_dashes[m_num_dashes++] = gap_len;
        }
    }


    //------------------------------------------------------------------------
    void vcgen_dash::dash_start(double ds)
    {
        m_dash_start = ds;
        calc_dash_start(std::fabs(ds));
    }


    //------------------------------------------------------------------------
    void vcgen_dash::calc_dash_start(double ds)
    {
        m_curr_dash = 0;
        m_curr_dash_start = 0.0;
        while(ds > 0.0)
        {
            if(ds > m_dashes[m_curr_dash])
            {
                ds -= m_dashes[m_curr_dash];
                ++m_curr_dash;
                m_curr_dash_start = 0.0;
                if(m_curr_dash >= m_num_dashes) m_curr_dash = 0;
            }
            else
            {
                m_curr_dash_start = ds;
                ds = 0.0;
            }
        }
    }


    //------------------------------------------------------------------------
    void vcgen_dash::remove_all()
    {
        m_status = initial;
        m_src_vertices.remove_all();
        m_closed = 0;
    }


    //------------------------------------------------------------------------
    void vcgen_dash::add_vertex(double x, double y, unsigned cmd)
    {
        m_status = initial;
        if(is_move_to(cmd))
        {
            m_src_vertices.modify_last(vertex_dist(x, y));
        }
        else
        {
            if(is_vertex(cmd))
            {
                m_src_vertices.add(vertex_dist(x, y));
            }
            else
            {
                m_closed = get_close_flag(cmd);
            }
        }
    }


    //------------------------------------------------------------------------
    void vcgen_dash::rewind(unsigned)
    {
        if(m_status == initial)
        {
            m_src_vertices.close(m_closed != 0);
            shorten_path(m_src_vertices, m_shorten, m_closed);
        }
        m_status = ready;
        m_src_vertex = 0;
    }

    //------------------------------------------------------------------------
    unsigned vcgen_dash::next_dash_vertex(double* x, double* y){
        double dash_rest = m_dashes[m_curr_dash] - m_curr_dash_start;

        unsigned cmd = (m_curr_dash & 1) ? 
                        path_cmd_move_to : 
                        path_cmd_line_to;

        if(m_curr_rest > dash_rest)
        {
            m_curr_rest -= dash_rest;
            ++m_curr_dash;
            if(m_curr_dash >= m_num_dashes) m_curr_dash = 0;
            m_curr_dash_start = 0.0;
            *x = m_v2->x - (m_v2->x - m_v1->x) * m_curr_rest / m_v1->dist;
            *y = m_v2->y - (m_v2->y - m_v1->y) * m_curr_rest / m_v1->dist;
        }
        else
        {
            m_curr_dash_start += m_curr_rest;
            *x = m_v2->x;
            *y = m_v2->y;
            ++m_src_vertex;
            m_v1 = m_v2;
            m_curr_rest = m_v1->dist;
            if(m_closed)
            {
                if(m_src_vertex > m_src_vertices.size())
                {
                    m_status = stop;
                }
                else
                {
                    m_v2 = &m_src_vertices
                    [
                        (m_src_vertex >= m_src_vertices.size()) ? 0 : 
                        m_src_vertex
                    ];
                }
            }
            else
            {
                if(m_src_vertex >= m_src_vertices.size())
                {
                    m_status = stop;
                }
                else
                {
                    m_v2 = &m_src_vertices[m_src_vertex];
                }
            }
        }
        return cmd;
    }

    //------------------------------------------------------------------------
    void vcgen_dash::init_state_vars(){
        m_src_vertex = 1;
        m_v1 = &m_src_vertices[0];
        m_v2 = &m_src_vertices[1];
        m_curr_rest = m_v1->dist;
        if(m_dash_start >= 0.0) calc_dash_start(m_dash_start);
    }

    //------------------------------------------------------------------------
    unsigned vcgen_dash::vertex(double* x, double* y)
    {
        unsigned cmd = path_cmd_move_to;
        while(!is_stop(cmd))
        {
            switch(m_status)
            {
            case initial:
                rewind(0);

            case ready:
                if(m_num_dashes < 2 || m_src_vertices.size() < 2)
                {
                    cmd = path_cmd_stop;
                    break;
                }
                this->init_state_vars();

                if(m_closed && (m_curr_dash & 1) == 0){ // if path is closed and the first dash-band is not a gap
                    this->m_status = skip_first_dash;
                    this->first_dash_skept = true;
                }else{
                    this->m_status = dashes;
                    this->first_dash_skept = false;
                }

                *x = m_v1->x;
                *y = m_v1->y;
                return path_cmd_move_to;

            case skip_first_dash:
                {
                    unsigned cmd = this->next_dash_vertex(x, y);
                    if(this->m_status == stop){ // if looped
                        if(this->first_dash_skept){
                            // the first dash has been skept in the beginning, so still need to return it in the end
                            m_status = first_dash;
                            this->init_state_vars();
                        }

                    }else if(cmd == path_cmd_line_to){
                        cmd = path_cmd_move_to;
                    }else if(this->m_status == skip_first_dash){ // if status did not change
                        this->m_status = dashes;
                    }
                    return cmd;
                }
            case first_dash:
                {
                    unsigned cmd = this->next_dash_vertex(x, y);
                    if(cmd != path_cmd_line_to){
                        cmd = path_cmd_stop;
                    }else if(m_status == stop){ // if looped
                        // this is the case when the whole closed path is covered by a single continuous dash,
                        // so we need to close the dash-path
                        cmd = unsigned(path_cmd_end_poly) | unsigned(path_flags_close);
                    }
                    return cmd;
                }
            case dashes:
                {
                    unsigned cmd = this->next_dash_vertex(x, y);
                    if(this->m_status == stop){ // if looped
                        if(this->first_dash_skept){
                            // the first dash has been skept in the beginning, so still need to return it in the end
                            m_status = first_dash;
                            this->init_state_vars();
                        }
                    }
                    return cmd;
                }
            case stop:
                cmd = path_cmd_stop;
                break;
            }

        }
        return path_cmd_stop;
    }


}

