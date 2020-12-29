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
#ifndef AGG_VCGEN_DASH_INCLUDED
#define AGG_VCGEN_DASH_INCLUDED

#include "agg_basics.h"
#include "agg_vertex_sequence.h"

namespace agg
{

    //---------------------------------------------------------------vcgen_dash
    //
    // See Implementation agg_vcgen_dash.cpp
    //
    class vcgen_dash
    {
        enum max_dashes_e
        {
            max_dashes = 32
        };

        enum status_e
        {
            initial,
            ready,
            skip_first_dash, // see description of 'first_dash_skept' flag below for info
            dashes,
            first_dash, // see description of 'first_dash_skept' flag below for info
            stop
        };

    public:
        typedef vertex_sequence<vertex_dist, 6> vertex_storage;

        vcgen_dash();

        void remove_all_dashes();
        void add_dash(double dash_len, double gap_len);
        void dash_start(double ds);

        void shorten(double s) { m_shorten = s; }
        double shorten() const { return m_shorten; }

        // Vertex Generator Interface
        void remove_all();
        void add_vertex(double x, double y, unsigned cmd);

        // Vertex Source Interface
        void     rewind(unsigned path_id);
        unsigned vertex(double* x, double* y);

    private:
        vcgen_dash(const vcgen_dash&);
        const vcgen_dash& operator = (const vcgen_dash&);

        void calc_dash_start(double ds);

        void init_state_vars();
        unsigned next_dash_vertex(double* x, double* y);

        double             m_dashes[max_dashes];
        double             m_total_dash_len;
        unsigned           m_num_dashes;
        double             m_dash_start;
        double             m_shorten;
        double             m_curr_dash_start;
        unsigned           m_curr_dash;
        double             m_curr_rest;
        const vertex_dist* m_v1;
        const vertex_dist* m_v2;

        vertex_storage m_src_vertices;
        unsigned       m_closed;
        status_e       m_status;
        unsigned       m_src_vertex;

        // For the case of closed paths the last dash should be merged with the first one.
        // To achieve that, if the path is closed, we skip the first dash and append it ti the last one.
        // This state flag indicates that the first dash has been skept.
        bool first_dash_skept;
    };


}

#endif
