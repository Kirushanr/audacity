/* SoX Resampler Library       Copyright (c) 2007-12 robs@users.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */



/* -------------------------------- Gubbins --------------------------------- */

#if !defined soxr_included
#define soxr_included


#if defined __cplusplus
  #include <cstddef>
  extern "C" {
#else
  #include <stddef.h>
#endif

#if defined SOXR_DLL
  #if defined soxr_EXPORTS
    #define SOXR __declspec(dllexport)
  #else
    #define SOXR __declspec(dllimport)
  #endif
#else
  #define SOXR
#endif

typedef struct soxr_io_spec soxr_io_spec_t;
typedef struct soxr_quality_spec soxr_quality_spec_t;
typedef struct soxr_runtime_spec soxr_runtime_spec_t;



/* ---------------------------- API conventions --------------------------------

Buffer lengths (and occupancies) are expressed as the number of contained
samples per channel.

Parameter names for buffer lengths have the suffix `len'.

A single-character `i' or 'o' is often used in names to give context as
input or output (e.g. ilen, olen).                                            */



/* --------------------------- Type declarations ---------------------------- */

typedef struct soxr * soxr_t;        /* A resampler for 1 or more channels. */
typedef char const * soxr_error_t;     /* 0:no-error; non-0:error. */

typedef void       * soxr_buf_t;  /* 1 buffer of channel-interleaved samples. */
typedef void const * soxr_cbuf_t;                        /* Ditto; read-only. */

typedef soxr_buf_t const  * soxr_bufs_t;/* Or, a separate buffer for each ch. */
typedef soxr_cbuf_t const * soxr_cbufs_t;                /* Ditto; read-only. */

typedef void const * soxr_in_t;      /* Either a soxr_cbuf_t or soxr_cbufs_t,
                                        depending on itype in soxr_io_spec_t. */
typedef void       * soxr_out_t;     /* Either a soxr_buf_t or soxr_bufs_t,
                                        depending on otype in soxr_io_spec_t. */



/* --------------------------- API main functions --------------------------- */

SOXR char const    * soxr_version(void);  /* Query library version: "x.y.z". */

#define soxr_strerror(e)               /* Soxr counterpart to strerror. */     \
    ((e)?(e):"no error")


/* Create a stream resampler: */

SOXR soxr_t soxr_create(
    double      input_rate,      /* Input sample-rate. */
    double      output_rate,     /* Output sample-rate. */
    unsigned    num_channels,    /* Number of channels to be used. */
        /* All following arguments are optional (may be set to NULL). */
    soxr_error_t *,              /* To report any error during creation. */
    soxr_io_spec_t const *,      /* To specify non-default I/O formats. */
    soxr_quality_spec_t const *, /* To specify non-default resampling quality.*/
    soxr_runtime_spec_t const *);/* To specify non-default runtime resources. */



/* If not using an app-supplied input function, after creating a stream
 * resampler, repeatedly call: */

SOXR soxr_error_t soxr_process(
    soxr_t      resampler,      /* As returned by soxr_create. */
                            /* Input (to be resampled): */
    soxr_in_t   in,             /* Input buffer(s); may be NULL (see below). */
    size_t      ilen,           /* Input buf. length (samples per channel). */
    size_t      * idone,        /* To return actual # samples used (<= ilen). */
                            /* Output (resampled): */
    soxr_out_t  out,            /* Output buffer(s).*/
    size_t      olen,           /* Output buf. length (samples per channel). */
    size_t      * odone);       /* To return actual # samples out (<= olen).

    Note that no special meaning is associated with ilen or olen equal to
    zero.  End-of-input (i.e. no data is available nor shall be available)
    may be indicated by seting `in' to NULL.                                  */



/* If using an app-supplied input function, it must look and behave like this:*/

typedef size_t /* data_len */
  (* soxr_input_fn_t)(         /* Supply data to be resampled. */
    void * input_fn_state,     /* As given to soxr_set_input_fn (below). */
    soxr_in_t * data,          /* Returned data; see below. N.B. ptr to ptr(s)*/
    size_t requested_len);     /* Samples per channel, >= returned data_len.

  data_len  *data     Indicates    Meaning
   ------- -------   ------------  -------------------------
     !=0     !=0       Success     *data contains data to be
                                   input to the resampler.
      0    !=0 (or   End-of-input  No data is available nor
           not set)                shall be available.
      0       0        Failure     An error occurred whilst trying to
                                   source data to be input to the resampler.  */

/* and be registered with a previously created stream resampler using: */

SOXR soxr_error_t soxr_set_input_fn(/* Set (or reset) an input function.*/
    soxr_t resampler,            /* As returned by soxr_create. */
    soxr_input_fn_t,             /* Function to supply data to be resampled.*/
    void * input_fn_state,       /* If needed by the input function. */
    size_t max_ilen);            /* Maximum value for input fn. requested_len.*/

/* then repeatedly call: */

SOXR size_t /*odone*/ soxr_output(/* Resample and output a block of data.*/
    soxr_t resampler,            /* As returned by soxr_create. */
    soxr_out_t data,             /* App-supplied buffer(s) for resampled data.*/
    size_t olen);                /* Amount of data to output; >= odone. */



/* Common stream resampler operations: */

SOXR soxr_error_t soxr_error(soxr_t);   /* Query error status. */
SOXR size_t     * soxr_num_clips(soxr_t); /* Query int. clip counter (for R/W). */
SOXR double       soxr_delay(soxr_t);   /* Query current delay in output samples.*/
SOXR char const * soxr_engine(soxr_t p);/* Query resampling engine name. */

SOXR soxr_error_t soxr_clear(soxr_t);   /* Ready for fresh signal, same config. */
SOXR void         soxr_delete(soxr_t);  /* Free resources. */



/* `Short-cut', single call to resample a (probably short) signal held entirely
 * in memory.  See soxr_create and soxr_process above for parameter details. */

SOXR soxr_error_t soxr_oneshot(
    double         input_rate,
    double         output_rate,
    unsigned       num_channels,
    soxr_in_t    in , size_t ilen, size_t * idone,
    soxr_out_t   out, size_t olen, size_t * odone,
    soxr_io_spec_t const *,
    soxr_quality_spec_t const *,
    soxr_runtime_spec_t const *);



/* For variable-rate resampling (experimental). See example # 5 for how to
 * create a variable-rate resampler and how to use this function. */

SOXR soxr_error_t soxr_set_io_ratio(soxr_t, double io_ratio, size_t slew_len);



/* -------------------------- API type definitions -------------------------- */

typedef enum {          /* Datatypes supported for I/O to/from the resampler: */
  /* Internal; do not use: */
  SOXR_FLOAT32, SOXR_FLOAT64, SOXR_INT32, SOXR_INT16, SOXR_SPLIT = 4,

  /* Use for interleaved channels: */
  SOXR_FLOAT32_I = SOXR_FLOAT32, SOXR_FLOAT64_I, SOXR_INT32_I, SOXR_INT16_I,

  /* Use for split channels: */
  SOXR_FLOAT32_S = SOXR_SPLIT  , SOXR_FLOAT64_S, SOXR_INT32_S, SOXR_INT16_S

} soxr_datatype_t;

#define soxr_datatype_size(x)  /* Returns `sizeof' a soxr_datatype_t sample. */\
  ((unsigned char *)"\4\10\4\2")[(x)&3]



struct soxr_io_spec {                                            /* Typically */
  soxr_datatype_t itype;     /* Input datatype.                SOXR_FLOAT32_I */
  soxr_datatype_t otype;     /* Output datatype.               SOXR_FLOAT32_I */
  double scale;              /* Linear gain to apply during resampling.  1    */
  void * e;                  /* Reserved for internal use                0    */
  unsigned long flags;       /* Per the following #defines.              0    */
};

#define SOXR_TPDF              0     /* Applicable only if otype is INT16. */
#define SOXR_NO_DITHER         8u    /* Disable the above. */



struct soxr_quality_spec {                                       /* Typically */
  double bits;               /* Required bit-accuracy (pass + stop).    20    */
  double phase;              /* Linear/minimum etc. phase. [0,100]      50    */
  double bw_pc;              /* Pass-band % (0dB pt.) to preserve.     91.3   */
  double anti_aliasing_pc;   /* % bandwidth without aliasing.           100   */
  void * e;                  /* Reserved for internal use.               0    */
  unsigned long flags;       /* Per the following #defines.              0    */
};

#define SOXR_ROLLOFF_SMALL     0u    /* <= 0.01 dB */
#define SOXR_ROLLOFF_MEDIUM    1u    /* <= 0.35 dB */
#define SOXR_ROLLOFF_NONE      2u    /* For Chebyshev bandwidth. */

#define SOXR_MAINTAIN_3DB_PT   4u  /* Reserved for internal use. */
#define SOXR_HI_PREC_CLOCK     8u  /* Increase `irrational' ratio accuracy. */
#define SOXR_DOUBLE_PRECISION 16u  /* Use double prec. even @ bitdepths <= 20.*/
#define SOXR_VR               32u  /* Experimental, variable-rate resampling. */



struct soxr_runtime_spec {                                       /* Typically */
  unsigned log2_min_dft_size;/* For DFT efficiency. [8,15]              10    */
  unsigned log2_large_dft_size;/* For DFT efficiency. [16,20]           17    */
  unsigned coef_size_kbytes; /* For SOXR_COEF_INTERP_AUTO (below).      400   */
  unsigned num_threads;      /* If built so. 0 means `automatic'.        1    */
  void * e;                  /* Reserved for internal use.               0    */
  unsigned long flags;       /* Per the following #defines.              0    */
};
                                   /* For `irrational' ratios only: */
#define SOXR_COEF_INTERP_AUTO  0u    /* Auto select coef. interpolation. */
#define SOXR_COEF_INTERP_LOW   1u    /* Man. select: less CPU, more memory. */
#define SOXR_COEF_INTERP_HIGH  2u    /* Man. select: more CPU, less memory. */

#define SOXR_STRICT_BUFFERING  4u  /* Reserved for future use. */
#define SOXR_NOSMALLINTOPT     8u  /* For test purposes only. */



/* -------------------------- API type constructors ------------------------- */

/* These functions allow setting of the most commonly-used structure
 * parameters, with other parameters being given default values.  The default
 * values may then be overridden, directly in the structure, if needed.  */

SOXR soxr_quality_spec_t soxr_quality_spec(
    unsigned long recipe,       /* Per the #defines immediately below. */
    unsigned long flags);       /* As soxr_quality_spec_t.flags. */

                                  /* The 5 standard qualities found in SoX: */
#define SOXR_QQ                 0   /* 'Quick' cubic interpolation. */
#define SOXR_LQ                 1   /* 'Low' 16-bit with larger rolloff. */
#define SOXR_MQ                 2   /* 'Medium' 16-bit with medium rolloff. */
#define SOXR_HQ                 SOXR_20_BITQ /* 'High quality'. */
#define SOXR_VHQ                SOXR_28_BITQ /* 'Very high quality'. */

#define SOXR_16_BITQ            3
#define SOXR_20_BITQ            4
#define SOXR_24_BITQ            5
#define SOXR_28_BITQ            6
#define SOXR_32_BITQ            7
                                    /* Libsamplerate equivalent qualities: */
#define SOXR_LSR0Q              8     /* 'Best sinc'. */
#define SOXR_LSR1Q              9     /* 'Medium sinc'. */
#define SOXR_LSR2Q              10    /* 'Fast sinc'. */

#define SOXR_LINEAR_PHASE       0x00
#define SOXR_INTERMEDIATE_PHASE 0x10
#define SOXR_MINIMUM_PHASE      0x30
#define SOXR_STEEP_FILTER       0x40
#define SOXR_ALLOW_ALIASING     0x80  /* Reserved for future use. */



SOXR soxr_runtime_spec_t soxr_runtime_spec(
    unsigned num_threads);



SOXR soxr_io_spec_t soxr_io_spec(
    soxr_datatype_t itype,
    soxr_datatype_t otype);



/* --------------------------- Internal use only ---------------------------- */

SOXR soxr_error_t soxr_set_error(soxr_t, soxr_error_t);
SOXR soxr_error_t soxr_set_num_channels(soxr_t, unsigned);



#undef SOXR

#if defined __cplusplus
}
#endif

#endif
