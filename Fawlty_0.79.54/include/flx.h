/*
 *  Copyright (c) 2000-2024 Lajos Foldy. All rights reserved.
 */
#ifndef flx_h
#define flx_h

#include <string>
#include <complex>
#include <vector>


#if __SIZEOF_POINTER__ == 8
  #define FLX_MEMORY_BITS   64
  #define FLX_ARG_SIZE      72
#endif
#if __SIZEOF_POINTER__ == 4
  #define FLX_MEMORY_BITS   32
  #define FLX_ARG_SIZE      48
#endif


#define FLX_FILE_BITS     64

#define FLX_ROUTINE(name) \
extern "C" { void name(const flx::c_arg& args); } \
void name(const flx::c_arg& args)

namespace fl { class c_error; }


namespace flx
{

typedef int          t_i32;
typedef unsigned int t_u32;

typedef long long          t_i64;
typedef unsigned long long t_u64;


typedef  signed char          t_i1;
typedef  signed short int     t_i2;
typedef  signed int           t_i4;
typedef  signed long long     t_i8;
typedef  unsigned char        t_u1;
typedef  unsigned short int   t_u2;
typedef  unsigned int         t_u4;
typedef  unsigned long long   t_u8;
typedef  float                t_f4;
typedef  double               t_f8;
typedef  std::complex<float>  t_c4;
typedef  std::complex<double> t_c8;
typedef  std::string          t_string;


#if   FLX_MEMORY_BITS==32
  typedef t_i4 t_im;
#elif FLX_MEMORY_BITS==64
  typedef t_i8 t_im;
#endif


#if   FLX_FILE_BITS==32
  typedef t_i32 t_if;
#elif FLX_FILE_BITS==64
  typedef t_i64 t_if;
#endif


void throw_error(const std::string& msg);

class c_data;   // forward declaration


class c_struct_def
{ public:
    c_struct_def(const std::string& name);

    void add_field(const std::string& name, c_data* val);

    void inherits(const std::string& name);

    ~c_struct_def() {}

  private:
    std::vector<std::string> m_tags;
    std::vector<c_data*> m_fields;
    std::string m_name;

    friend class c_data;
};


class c_data
{ public:
    enum e_type
       { T_U1=0,
         T_I1=1,
         T_U2=2,
         T_I2=3,
         T_U4=4,
         T_I4=5,
         T_F4=6,
         T_F8=7,
         T_U8=8,
         T_I8=9,
         T_C4=10,
         T_C8=11,

         T_STRING =12,
         T_STRUCT =13,
         T_POINTER=14,
         T_OBJECT =15,

         T_UNDEF=16,

#if   FLX_MEMORY_BITS==32
         T_IM=T_I4
#elif FLX_MEMORY_BITS==64
         T_IM=T_I8
#endif
       };

    c_data();

    c_data(const c_data& src) { assign(&src); }

    c_data& operator=(const c_data& src)
         { assign(&src);
           return *this;
         }

    void set_i1(t_i1 val);
    void set_u1(t_u1 val);
    void set_i2(t_i2 val);
    void set_u2(t_u2 val);
    void set_i4(t_i4 val);
    void set_u4(t_u4 val);
    void set_i8(t_i8 val);
    void set_u8(t_u8 val);
    void set_f4(t_f4 val);
    void set_f8(t_f8 val);
    void set_c4(t_c4 val);
    void set_c8(t_c8 val);

#if   FLX_MEMORY_BITS==32
     void set_im(t_im val) { set_i4(val); }
#elif FLX_MEMORY_BITS==64
     void set_im(t_im val) { set_i8(val); }
#endif

    void set_string(const t_string& val);


    void create_struct(const std::string& name);

    void create_struct(const c_struct_def& sd);

    void create_pointer(int alloc);

    void create_array(e_type type, int ndim, const t_im* dims);

    void create_struct_array(const std::string& name, int ndim, const t_im* dims);

    void create_struct_array(const c_struct_def& sd, int ndim, const t_im* dims);


    e_type get_type();

    t_im get_size();

    void* get_address();


    int get_array_ndim();

    const t_im* get_array_dims();

    t_im get_array_dim(int i);
    t_im get_array_str(int i);

    t_im get_array_size();

    void* get_array_address();


    t_i1 get_i1();
    t_u1 get_u1();
    t_i2 get_i2();
    t_u2 get_u2();
    t_i4 get_i4();
    t_u4 get_u4();
    t_i8 get_i8();
    t_u8 get_u8();
    t_f4 get_f4();
    t_f8 get_f8();
    t_c4 get_c4();
    t_c8 get_c8();

#if   FLX_MEMORY_BITS==32
     t_im get_im() { return get_i4(); }
#elif FLX_MEMORY_BITS==64
     t_im get_im() { return get_i8(); }
#endif

    t_string get_string();


    void check_type(e_type type);

    void check_defined();

    void check_scalar();

    void check_array();

    void check_array_ndim(int val);

    void check_array_dim(int n, t_im val);

    void check_num();

    void check_var();


    int is_scalar();

    int is_array();

    int key_set();

    int is_true();

    int is_zero();

    int is_var();

    int is_tmp();


    std::string get_struct_name();

    int get_struct_ntag();

    void get_struct_tags(std::vector<std::string>* tags);


    c_data* get_heap_var();


    void convert(c_data* src, e_type type);

    t_im convert_to_im();

    void assign(const c_data* src);

    void move(c_data* src);

    void undef();


   ~c_data();

  private:
    union
    { char m_data[32];
      double m_align8;
    };
};


template<typename T>
c_data::e_type
get_data_type()
{
    throw_error("invalid type");
    return c_data::T_UNDEF;
}

template<> c_data::e_type get_data_type<t_u1>() { return c_data::T_U1; }
template<> c_data::e_type get_data_type<t_u2>() { return c_data::T_U2; }
template<> c_data::e_type get_data_type<t_u4>() { return c_data::T_U4; }
template<> c_data::e_type get_data_type<t_u8>() { return c_data::T_U8; }
template<> c_data::e_type get_data_type<t_i1>() { return c_data::T_I1; }
template<> c_data::e_type get_data_type<t_i2>() { return c_data::T_I2; }
template<> c_data::e_type get_data_type<t_i4>() { return c_data::T_I4; }
template<> c_data::e_type get_data_type<t_i8>() { return c_data::T_I8; }
template<> c_data::e_type get_data_type<t_f4>() { return c_data::T_F4; }
template<> c_data::e_type get_data_type<t_f8>() { return c_data::T_F8; }
template<> c_data::e_type get_data_type<t_c4>() { return c_data::T_C4; }
template<> c_data::e_type get_data_type<t_c8>() { return c_data::T_C8; }

template<> c_data::e_type get_data_type<t_string>()
  { return c_data::T_STRING; }


static inline t_im
get_elem_size(c_data::e_type type)
{
    switch ( type )
    { case c_data::T_U1:   return sizeof(t_u1);
      case c_data::T_U2:   return sizeof(t_u2);
      case c_data::T_U4:   return sizeof(t_u4);
      case c_data::T_U8:   return sizeof(t_u8);
      case c_data::T_I1:   return sizeof(t_i1);
      case c_data::T_I2:   return sizeof(t_i2);
      case c_data::T_I4:   return sizeof(t_i4);
      case c_data::T_I8:   return sizeof(t_i8);
      case c_data::T_F4:   return sizeof(t_f4);
      case c_data::T_F8:   return sizeof(t_f8);
      case c_data::T_C4:   return sizeof(t_c4);
      case c_data::T_C8:   return sizeof(t_c8);

      case c_data::T_STRING:   return sizeof(t_string);

      default:   throw_error("invalid type");
    }

    return 0;
}


template<typename T, t_im N=1>
class c_elem_access
{ public:
    c_elem_access(c_data* data)
         { if ( N<1 ) throw_error("N must be greater than zero");
           data->check_defined();

           m_type_src=data->get_type();
           m_type_dst=get_data_type<T>();
           m_addr=data->get_address();
           m_size=data->get_size();
           m_elem=get_elem_size(m_type_src);
         }

    T& operator[](t_im pos)
         { check(pos);
           if ( m_type_src==m_type_dst ) return *((T*)m_addr+pos);
           convert(1, m_type_src, (char*)m_addr+pos*m_elem,
                      m_type_dst, m_value);
           return m_value[0];
         }

    T* operator()(t_im pos)
         { check(N*pos);
           if ( N>1 ) check(N*pos+N-1);
           if ( m_type_src==m_type_dst ) return (T*)m_addr+N*pos;
           convert(N, m_type_src, (char*)m_addr+N*pos*m_elem,
                      m_type_dst, m_value);
           return m_value;
         }

    ~c_elem_access() {}

  private:
    c_data::e_type m_type_src;
    c_data::e_type m_type_dst;
    void* m_addr;
    t_im m_size;
    t_im m_elem;
    T m_value[N];

    void check(t_im pos)
         { if ( (pos<0) || (pos>=m_size) ) throw_error("range error"); }
};


class c_arg
{ public:
    c_arg();

    int get_npos() const;

    int get_nkey() const;

    c_data* get_pos(int i) const;

    c_data* get_key(const std::string& key) const;

    c_data* get_return() const;

   ~c_arg();

  private:
    union
    { char m_data[FLX_ARG_SIZE];
      double m_align8;
    };

    c_arg(const c_arg& src);

    c_arg& operator=(const c_arg& src);
};


void op_neg(c_data* op, c_data* res);;
void op_bit_not(c_data* op, c_data* res);;
void op_log_not(c_data* op, c_data* res);;

void op_add(c_data* op1, c_data* op2, c_data* res);
void op_sub(c_data* op1, c_data* op2, c_data* res);
void op_mul(c_data* op1, c_data* op2, c_data* res);
void op_div(c_data* op1, c_data* op2, c_data* res);
void op_mod(c_data* op1, c_data* op2, c_data* res);
void op_pow(c_data* op1, c_data* op2, c_data* res);
void op_min(c_data* op1, c_data* op2, c_data* res);
void op_max(c_data* op1, c_data* op2, c_data* res);
void op_eq(c_data* op1, c_data* op2, c_data* res);
void op_ne(c_data* op1, c_data* op2, c_data* res);
void op_ge(c_data* op1, c_data* op2, c_data* res);
void op_gt(c_data* op1, c_data* op2, c_data* res);
void op_le(c_data* op1, c_data* op2, c_data* res);
void op_lt(c_data* op1, c_data* op2, c_data* res);
void op_bit_and(c_data* op1, c_data* op2, c_data* res);
void op_bit_or(c_data* op1, c_data* op2, c_data* res);
void op_bit_xor(c_data* op1, c_data* op2, c_data* res);


std::string get_error_msg(const fl::c_error& error);

int is_struct_defined(const std::string& name);

void print(const std::string& msg);

void print_nl(const std::string& msg);

void convert(t_im n, c_data::e_type src_type, void* src, c_data::e_type dst_type, void* dst);


class c_routine_call
{ public:
    enum e_type { T_FUN, T_PRO };

    c_routine_call(const std::string& name, e_type type);

    void add_pos(c_data* val);

    void add_key(const std::string& key, c_data* val);

    void set_return(c_data* val);

    void call();

    ~c_routine_call();

  private:
    std::vector<c_data*> m_pos;
    std::vector<c_data*> m_key;
    std::vector<std::string> m_keywords;
    std::string m_name;
    c_data* m_return;
    e_type m_type;

    c_routine_call(const c_routine_call& src);

    c_routine_call& operator=(const c_routine_call& src);
};

}

#endif
