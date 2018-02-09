/*
 *
 *                   _/_/_/    _/_/   _/    _/ _/_/_/    _/_/
 *                  _/   _/ _/    _/ _/_/  _/ _/   _/ _/    _/
 *                 _/_/_/  _/_/_/_/ _/  _/_/ _/   _/ _/_/_/_/
 *                _/      _/    _/ _/    _/ _/   _/ _/    _/
 *               _/      _/    _/ _/    _/ _/_/_/  _/    _/
 *
 *             ***********************************************
 *                              PandA Project 
 *                     URL: http://panda.dei.polimi.it
 *                       Politecnico di Milano - DEIB
 *                        System Architectures Group
 *             ***********************************************
 *              Copyright (c) 2004-2018 Politecnico di Milano
 *
 *   This file is part of the PandA framework.
 *
 *   The PandA framework is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/
/**
 * @file token_interface.cpp
 * @brief Implementation of interface to token objects.
 *
 * Interface implementation to token objects.
 *
 * @author Fabrizio Ferrandi <ferrandi.elet.polimi.it>
 * @author Marco Lattuada <lattuada@elet.polimi.it>
 * @version $Revision$
 * @date $Date$
 * Last modified by $Author$
 *
*/
///Header include
#include "token_interface.hpp"

///STD include
#include <cstring>
#include <fstream>
#include <iosfwd>
#include "config_HAVE_BISON_2_7_OR_GREATER.hpp"

///Utility include
#include "refcount.hpp"

///NOTE: forward declarations of BisonParserData and TreeFlexLexer are in this point since they will be used in treeParser.h
REF_FORWARD_DECL(BisonParserData);
REF_FORWARD_DECL(TreeFlexLexer);

///Tree include
#if HAVE_BISON_2_7_OR_GREATER
#include "treeParser.hpp"
#else
#include "treeParser.h"
#endif

///Utility include
#include <boost/lexical_cast.hpp>
#include "exceptions.hpp"

#define NO_TOKEN -1

const int treeVocabularyTokenTypes::bisontokens[] =
{
   TOK_BISON_GCC_VERSION,
   TOK_BISON_PLUGIN_VERSION,
   TOK_BISON_IDENTIFIER_NODE,
   TOK_BISON_TREE_LIST,
   TOK_BISON_TREE_VEC,
   TOK_BISON_BLOCK,
   TOK_BISON_VOID_TYPE,
   TOK_BISON_INTEGER_TYPE,
   TOK_BISON_REAL_TYPE,
   TOK_BISON_COMPLEX_TYPE,
   TOK_BISON_TYPE_ARGUMENT_PACK,
   TOK_BISON_NONTYPE_ARGUMENT_PACK,
   TOK_BISON_EXPR_PACK_EXPANSION,
   TOK_BISON_VECTOR_TYPE,
   TOK_BISON_ENUMERAL_TYPE,
   TOK_BISON_BOOLEAN_TYPE,
   TOK_BISON_CHAR_TYPE,
   TOK_BISON_NULLPTR_TYPE,
   TOK_BISON_ERROR_MARK,
   TOK_BISON_TYPE_PACK_EXPANSION,
   TOK_BISON_POINTER_TYPE,
   TOK_BISON_OFFSET_TYPE,
   TOK_BISON_REFERENCE_TYPE,
   TOK_BISON_METHOD_TYPE,
   TOK_BISON_ARRAY_TYPE,
   TOK_BISON_SET_TYPE,
   TOK_BISON_RECORD_TYPE,
   TOK_BISON_UNION_TYPE,
   TOK_BISON_QUAL_UNION_TYPE,
   TOK_BISON_FUNCTION_TYPE,
   TOK_BISON_LANG_TYPE,
   TOK_BISON_INTEGER_CST,
   TOK_BISON_REAL_CST,
   TOK_BISON_COMPLEX_CST,
   TOK_BISON_VECTOR_CST,
   TOK_BISON_VOID_CST,
   TOK_BISON_STRING_CST,
   TOK_BISON_FUNCTION_DECL,
   TOK_BISON_LABEL_DECL,
   TOK_BISON_CONST_DECL,
   TOK_BISON_TYPE_DECL,
   TOK_BISON_USING_DECL,
   TOK_BISON_VAR_DECL,
   TOK_BISON_PARM_DECL,
   TOK_BISON_PARAM_PACKS,
   TOK_BISON_RESULT_DECL,
   TOK_BISON_FIELD_DECL,
   TOK_BISON_NAMESPACE_DECL,
   TOK_BISON_TRANSLATION_UNIT_DECL,
   TOK_BISON_COMPONENT_REF,
   TOK_BISON_BIT_FIELD_REF,
   TOK_BISON_INDIRECT_REF,
   TOK_BISON_MISALIGNED_INDIRECT_REF,
   TOK_BISON_BUFFER_REF,
   TOK_BISON_ARRAY_REF,
   TOK_BISON_ARRAY_RANGE_REF,
   TOK_BISON_VTABLE_REF,
   TOK_BISON_CONSTRUCTOR,
   TOK_BISON_DESTRUCTOR,
   TOK_BISON_COMPOUND_EXPR,
   TOK_BISON_MODIFY_EXPR,
   TOK_BISON_GIMPLE_ASSIGN,
   TOK_BISON_INIT_EXPR,
   TOK_BISON_TARGET_EXPR,
   TOK_BISON_COND_EXPR,
   TOK_BISON_GIMPLE_COND,
   NO_TOKEN,
   NO_TOKEN,
   TOK_BISON_GIMPLE_BIND,
   TOK_BISON_GIMPLE_CALL,
   TOK_BISON_CALL_EXPR,
   TOK_BISON_AGGR_INIT_EXPR,
   TOK_BISON_GIMPLE_NOP, 
   TOK_BISON_WITH_CLEANUP_EXPR,
   TOK_BISON_CLEANUP_POINT_EXPR,
   TOK_BISON_PLACEHOLDER_EXPR,
   TOK_BISON_REDUC_MAX_EXPR,
   TOK_BISON_REDUC_MIN_EXPR,
   TOK_BISON_REDUC_PLUS_EXPR,
   TOK_BISON_PLUS_EXPR,
   TOK_BISON_TERNARY_PLUS_EXPR,
   TOK_BISON_TERNARY_PM_EXPR,
   TOK_BISON_TERNARY_MP_EXPR,
   TOK_BISON_TERNARY_MM_EXPR,
   TOK_BISON_BIT_IOR_CONCAT_EXPR,
   TOK_BISON_MINUS_EXPR,
   TOK_BISON_MULT_EXPR,
   TOK_BISON_TRUNC_DIV_EXPR,
   TOK_BISON_CEIL_DIV_EXPR,
   TOK_BISON_FLOOR_DIV_EXPR,
   TOK_BISON_ROUND_DIV_EXPR,
   TOK_BISON_TRUNC_MOD_EXPR,
   TOK_BISON_CEIL_MOD_EXPR,
   TOK_BISON_FLOOR_MOD_EXPR,
   TOK_BISON_ROUND_MOD_EXPR,
   TOK_BISON_RDIV_EXPR,
   TOK_BISON_EXACT_DIV_EXPR,
   TOK_BISON_FIX_TRUNC_EXPR,
   TOK_BISON_FIX_CEIL_EXPR,
   TOK_BISON_FIX_FLOOR_EXPR,
   TOK_BISON_FIX_ROUND_EXPR,
   TOK_BISON_FLOAT_EXPR,
   TOK_BISON_LUT_EXPR,
   TOK_BISON_NEGATE_EXPR,
   TOK_BISON_MIN_EXPR,
   TOK_BISON_MAX_EXPR,
   TOK_BISON_ABS_EXPR,
   TOK_BISON_LSHIFT_EXPR,
   TOK_BISON_RSHIFT_EXPR,
   TOK_BISON_LROTATE_EXPR,
   TOK_BISON_RROTATE_EXPR,
   TOK_BISON_BIT_IOR_EXPR,
   TOK_BISON_BIT_XOR_EXPR,
   TOK_BISON_BIT_AND_EXPR,
   TOK_BISON_BIT_NOT_EXPR,
   TOK_BISON_TRUTH_ANDIF_EXPR,
   TOK_BISON_TRUTH_ORIF_EXPR,
   TOK_BISON_TRUTH_AND_EXPR,
   TOK_BISON_TRUTH_OR_EXPR,
   TOK_BISON_TRUTH_XOR_EXPR,
   TOK_BISON_TRUTH_NOT_EXPR,
   TOK_BISON_LT_EXPR,
   TOK_BISON_LE_EXPR,
   TOK_BISON_GT_EXPR,
   TOK_BISON_GE_EXPR,
   TOK_BISON_EQ_EXPR,
   TOK_BISON_NE_EXPR,
   TOK_BISON_UNORDERED_EXPR,
   TOK_BISON_ORDERED_EXPR,
   TOK_BISON_UNLT_EXPR,
   TOK_BISON_UNLE_EXPR,
   TOK_BISON_UNGT_EXPR,
   TOK_BISON_UNGE_EXPR,
   TOK_BISON_UNEQ_EXPR,
   TOK_BISON_LTGT_EXPR,
   TOK_BISON_IN_EXPR,
   TOK_BISON_SET_LE_EXPR,
   TOK_BISON_CARD_EXPR,
   TOK_BISON_RANGE_EXPR,
   TOK_BISON_PAREN_EXPR,
   TOK_BISON_CONVERT_EXPR,
   TOK_BISON_NOP_EXPR,
   TOK_BISON_NON_LVALUE_EXPR,
   TOK_BISON_VIEW_CONVERT_EXPR,
   TOK_BISON_SAVE_EXPR,
   TOK_BISON_UNSAVE_EXPR,
   TOK_BISON_ADDR_EXPR,
   TOK_BISON_REFERENCE_EXPR,
   TOK_BISON_FDESC_EXPR,
   TOK_BISON_COMPLEX_EXPR,
   TOK_BISON_CONJ_EXPR,
   TOK_BISON_REALPART_EXPR,
   TOK_BISON_IMAGPART_EXPR,
   TOK_BISON_PREDECREMENT_EXPR,
   TOK_BISON_PREINCREMENT_EXPR,
   TOK_BISON_POSTDECREMENT_EXPR,
   TOK_BISON_POSTINCREMENT_EXPR,
   TOK_BISON_VA_ARG_EXPR,
   TOK_BISON_TRY_CATCH_EXPR,
   TOK_BISON_TRY_FINALLY,
   TOK_BISON_,
   TOK_BISON_GIMPLE_GOTO,
   TOK_BISON_GOTO_SUBROUTINE,
   TOK_BISON_GIMPLE_RETURN,
   TOK_BISON_EXIT_EXPR,
   TOK_BISON_LOOP_EXPR,
   TOK_BISON_GIMPLE_SWITCH,
   TOK_BISON_GIMPLE_MULTI_WAY_IF,
   TOK_BISON_CASE_LABEL_EXPR,
   TOK_BISON_GIMPLE_RESX,
   TOK_BISON_GIMPLE_ASM,
   TOK_BISON_SSA_NAME,
   TOK_BISON_ADDR_STMT,
   TOK_BISON_DEF_STMT,
   TOK_BISON_USE_STMT,
   TOK_BISON_GIMPLE_PHI,
   TOK_BISON_CATCH_EXPR,
   TOK_BISON_EH_FILTER_EXPR,
   TOK_BISON_STATEMENT_LIST,
   TOK_BISON_TEMPLATE_DECL,
   TOK_BISON_TEMPLATE_TYPE_PARM,
   TOK_BISON_CAST_EXPR,
   TOK_BISON_STATIC_CAST_EXPR,
   TOK_BISON_TYPENAME_TYPE,
   TOK_BISON_SIZEOF_EXPR,
   TOK_BISON_SCOPE_REF,
   TOK_BISON_CTOR_INITIALIZER,
   TOK_BISON_DO_STMT,
   TOK_BISON_EXPR_STMT,
   TOK_BISON_FOR_STMT,
   TOK_BISON_IF_STMT,
   TOK_BISON_RETURN_STMT,
   TOK_BISON_WHILE_STMT,
   TOK_BISON_MODOP_EXPR,
   TOK_BISON_NEW_EXPR,
   TOK_BISON_VEC_COND_EXPR,
   TOK_BISON_VEC_PERM_EXPR,
   TOK_BISON_DOT_PROD_EXPR,
   TOK_BISON_VEC_LSHIFT_EXPR,
   TOK_BISON_VEC_RSHIFT_EXPR,
   TOK_BISON_WIDEN_MULT_HI_EXPR,
   TOK_BISON_WIDEN_MULT_LO_EXPR,
   TOK_BISON_VEC_UNPACK_HI_EXPR,
   TOK_BISON_VEC_UNPACK_LO_EXPR,
   TOK_BISON_VEC_UNPACK_FLOAT_HI_EXPR,
   TOK_BISON_VEC_UNPACK_FLOAT_LO_EXPR,
   TOK_BISON_VEC_PACK_TRUNC_EXPR,
   TOK_BISON_VEC_PACK_SAT_EXPR,
   TOK_BISON_VEC_PACK_FIX_TRUNC_EXPR,
   TOK_BISON_VEC_EXTRACTEVEN_EXPR,
   TOK_BISON_VEC_EXTRACTODD_EXPR,
   TOC_BISON_VEC_INTERLEAVEHIGH_EXPR,
   TOC_BISON_VEC_INTERLEAVELOW_EXPR,
   TOK_BISON_VEC_NEW_EXPR,
   TOK_BISON_OVERLOAD,
   TOK_BISON_REINTERPRET_CAST_EXPR,
   TOK_BISON_TEMPLATE_ID_EXPR,
   TOK_BISON_THROW_EXPR,
   TOK_BISON_TRY_BLOCK,
   TOK_BISON_ARROW_EXPR,
   TOK_BISON_HANDLER,
   TOK_BISON_BASELINK,

   TOK_BISON_NAME,
   TOK_BISON_TYPE,
   TOK_BISON_SRCP,
   TOK_BISON_ARG,
   TOK_BISON_BODY,
   TOK_BISON_STRG,
   TOK_BISON_LNGT,
   TOK_BISON_SIZE,
   TOK_BISON_ALGN,
   TOK_BISON_RETN,
   TOK_BISON_PRMS,
   TOK_BISON_SCPE,
   TOK_BISON_BB_INDEX,
   TOK_BISON_USED,
   TOK_BISON_VALUE,
   TOK_BISON_ARGT,
   TOK_BISON_PREC,
   TOK_BISON_MIN,
   TOK_BISON_MAX,
   TOK_BISON_BIT_VALUES,
   TOK_BISON_VALU,
   TOK_BISON_CHAN,
   TOK_BISON_STMT,
   TOK_BISON_OP,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   TOK_BISON_VARS,
   TOK_BISON_UNQL,
   TOK_BISON_ELTS,
   TOK_BISON_DOMN,
   TOK_BISON_BLOC,
   TOK_BISON_DCLS,
   TOK_BISON_MNGL,
   TOK_BISON_PTD,
   TOK_BISON_REFD,
   TOK_BISON_QUAL,
   TOK_BISON_VALR,
   TOK_BISON_VALX,
   TOK_BISON_FLDS,
   TOK_BISON_VFLD,
   TOK_BISON_BPOS,
   TOK_BISON_FN,
   TOK_BISON_GOTO,
   TOK_BISON_REAL,
   TOK_BISON_IMAG,
   TOK_BISON_BASES,
   TOK_BISON_BINFO,
   TOK_BISON_PUB,
   TOK_BISON_PROT,
   TOK_BISON_PRIV,
   TOK_BISON_BINF,
   TOK_BISON_UID,
   TOK_BISON_OLD_UID,
   TOK_BISON_INIT,
   TOK_BISON_FINI,
   TOK_BISON_PURP,
   TOK_BISON_PRED,
   TOK_BISON_SUCC,
   TOK_BISON_PHI,
   TOK_BISON_RES,
   TOK_BISON_DEF,
   TOK_BISON_EDGE,
   TOK_BISON_VAR,
   TOK_BISON_VERS,
   TOK_BISON_ORIG_VERS,
   TOK_BISON_CNST,
   TOK_BISON_CLAS,
   TOK_BISON_DECL,
   TOK_BISON_CLNP,
   TOK_BISON_LAB,
   TOK_BISON_TRY,
   TOK_BISON_EX,
   TOK_BISON_OUT,
   TOK_BISON_IN,
   TOK_BISON_STR,
   TOK_BISON_CLOB,
   TOK_BISON_CLOBBER,
   TOK_BISON_REF,
   TOK_BISON_FNCS,
   TOK_BISON_CSTS,
   TOK_BISON_RSLT,
   TOK_BISON_INST,
   TOK_BISON_SPCS,
   TOK_BISON_CLS,
   TOK_BISON_BFLD,
   TOK_BISON_CTOR,
   TOK_BISON_NEXT,
   TOK_BISON_COND,
   TOK_BISON_EXPR,
   TOK_BISON_THEN,
   TOK_BISON_ELSE,
   TOK_BISON_CRNT,
   TOK_BISON_HDLR,
   TOK_BISON_ARTIFICIAL,
   TOK_BISON_SYSTEM,
   TOK_BISON_OPERATING_SYSTEM,
   TOK_BISON_LIBRARY_SYSTEM,
   TOK_BISON_LIBBAMBU,
   TOK_BISON_EXTERN,
   TOK_BISON_C,
   TOK_BISON_LSHIFT,
   TOK_BISON_GLOBAL_INIT,
   TOK_BISON_GLOBAL_FINI,
   TOK_BISON_UNDEFINED,
   TOK_BISON_BUILTIN,
   TOK_BISON_HWCALL,
   TOK_BISON_OPERATOR,
   TOK_BISON_OVERFLOW,
   TOK_BISON_VIRT,
   TOK_BISON_UNSIGNED,
   TOK_BISON_STRUCT,
   TOK_BISON_UNION,
   TOK_BISON_CONSTANT,
   TOK_BISON_READONLY,
   TOK_BISON_REGISTER,
   TOK_BISON_STATIC,
   NO_TOKEN,
   TOK_BISON_REVERSE_RESTRICT,
   TOK_BISON_OMP_ATOMIC,
   TOK_BISON_OMP_BODY_LOOP,
   TOK_BISON_OMP_CRITICAL_SESSION,
   TOK_BISON_OMP_FOR_WRAPPER,
   TOK_BISON_DEFAULT,
   TOK_BISON_VOLATILE,
   TOK_BISON_VARARGS,
   TOK_BISON_INF,
   TOK_BISON_NAN,
   TOK_BISON_ENTRY,
   TOK_BISON_EXIT,
   TOK_BISON_NEW,
   TOK_BISON_DELETE,
   TOK_BISON_ASSIGN,
   TOK_BISON_MEMBER,
   TOK_BISON_PUBLIC,
   TOK_BISON_PRIVATE,
   TOK_BISON_PROTECTED,
   TOK_BISON_NORETURN,
   TOK_BISON_NOINLINE,
   TOK_BISON_ALWAYS_INLINE,
   TOK_BISON_UNUSED,
   TOK_BISON_CONST,
   TOK_BISON_TRANSPARENT_UNION,
   TOK_BISON_MODE,
   TOK_BISON_SECTION,
   TOK_BISON_ALIGNED,
   TOK_BISON_PACKED,
   TOK_BISON_WEAK,
   TOK_BISON_ALIAS,
   TOK_BISON_NO_INSTRUMENT_FUNCTION,
   TOK_BISON_MALLOC,
   TOK_BISON_NO_STACK_LIMIT,
   TOK_BISON_NO_STACK,
   TOK_BISON_PURE,
   TOK_BISON_DEPRECATED,
   TOK_BISON_VECTOR_SIZE,
   TOK_BISON_VISIBILITY,
   TOK_BISON_TLS_MODEL,
   TOK_BISON_NONNULL,
   TOK_BISON_NOTHROW,
   TOK_BISON_MAY_ALIAS,
   TOK_BISON_WARN_UNUSED_RESULT,
   TOK_BISON_FORMAT,
   TOK_BISON_FORMAT_ARG,
   TOK_BISON_NULL,
   TOK_BISON_CONVERSION,
   TOK_BISON_VIRTUAL,
   TOK_BISON_MUTABLE,
   TOK_BISON_PSEUDO_TMPL,
   TOK_BISON_SPEC,
   TOK_BISON_LINE,
   TOK_BISON_FIXD,

   TOK_BISON_VECNEW,
   TOK_BISON_VECDELETE,
   TOK_BISON_POS,
   TOK_BISON_NEG,
   TOK_BISON_ADDR,
   TOK_BISON_DEREF,
   TOK_BISON_NOT,
   TOK_BISON_LNOT,
   TOK_BISON_PREINC,
   TOK_BISON_PREDEC,
   TOK_BISON_PLUSASSIGN,
   TOK_BISON_PLUS,
   TOK_BISON_MINUSASSIGN,
   TOK_BISON_MINUS,
   TOK_BISON_MULTASSIGN,
   TOK_BISON_MULT,
   TOK_BISON_DIVASSIGN,
   TOK_BISON_DIV,
   TOK_BISON_MODASSIGN,
   TOK_BISON_MOD,
   TOK_BISON_ANDASSIGN,
   TOK_BISON_AND,
   TOK_BISON_ORASSIGN,
   TOK_BISON_OR,
   TOK_BISON_XORASSIGN,
   TOK_BISON_XOR,
   TOK_BISON_LSHIFTASSIGN,
   TOK_BISON_RSHIFTASSIGN,
   TOK_BISON_RSHIFT,
   TOK_BISON_EQ,
   TOK_BISON_NE,
   TOK_BISON_LT,
   TOK_BISON_GT,
   TOK_BISON_LE,
   TOK_BISON_GE,
   TOK_BISON_LAND,
   TOK_BISON_LOR,
   TOK_BISON_COMPOUND,
   TOK_BISON_MEMREF,
   TOK_BISON_SUBS,
   TOK_BISON_POSTINC,
   TOK_BISON_POSTDEC,
   TOK_BISON_CALL,
   TOK_BISON_THUNK,
   TOK_BISON_THIS_ADJUSTING,
   TOK_BISON_RESULT_ADJUSTING,
   TOK_BISON_PTRMEM,
   TOK_BISON_QUAL_R,
   TOK_BISON_QUAL_V,
   TOK_BISON_QUAL_VR,
   TOK_BISON_QUAL_C,
   TOK_BISON_QUAL_CR,
   TOK_BISON_QUAL_CV,
   TOK_BISON_QUAL_CVR,

   TOK_BISON_USE_TMPL,
   TOK_BISON_TMPL_PARMS,
   TOK_BISON_TMPL_ARGS,
   TOK_BISON_TEMPLATE_PARM_INDEX,
   TOK_BISON_INDEX,
   TOK_BISON_LEVEL,
   TOK_BISON_ORIG_LEVEL,
   TOK_BISON_INLINE_BODY,
   TOK_BISON_BITFIELD,
   TOK_BISON_WITH_SIZE_EXPR,
   TOK_BISON_OBJ_TYPE_REF,
   TOK_BISON_MEMUSE,
   TOK_BISON_MEMDEF,
   TOK_BISON_VUSE,
   TOK_BISON_VDEF,
   TOK_BISON_VOVER,
   TOK_BISON_PTR_INFO,
   TOK_BISON_TRUE_EDGE,
   TOK_BISON_FALSE_EDGE,
   TOK_BISON_POINTER_PLUS_EXPR,
   TOK_BISON_TARGET_MEM_REF,
   TOK_BISON_TARGET_MEM_REF461,
   TOK_BISON_MEM_REF,
   TOK_BISON_WIDEN_SUM_EXPR,
   TOK_BISON_WIDEN_MULT_EXPR,
   TOK_BISON_MULT_HIGHPART_EXPR,
   TOK_BISON_ASSERT_EXPR,
   TOK_BISON_SYMBOL,
   TOK_BISON_BASE,
   TOK_BISON_IDX,
   TOK_BISON_IDX2,
   TOK_BISON_STEP,
   TOK_BISON_OFFSET,
   TOK_BISON_ORIG,
   TOK_BISON_TAG,
   TOK_BISON_SMT_ANN,
   TOK_BISON_TRAIT_EXPR,
   TOK_BISON_TIME_WEIGHT,
   TOK_BISON_SIZE_WEIGHT,
   TOK_BISON_RTL_SIZE_WEIGHT,
   TOK_BISON_HPL,
   TOK_BISON_LOOP_ID,
   TOK_BISON_ATTRIBUTES,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   TOK_BISON_GIMPLE_PREDICT,
   TOK_BISON_CLB,
   TOK_BISON_CLB_VARS,
   TOK_BISON_USE,
   TOK_BISON_USE_VARS,
   TOK_BISON_PREDICATE,
   TOK_BISON_SLOT,

   ///RTL token
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,
   NO_TOKEN,

   static_cast<const int>(TreeVocabularyTokenTypes_TokenEnum::LAST_TOKEN)
};

const char* treeVocabularyTokenTypes::tokenNames[] =
{
   "GCC_VERSION",
   "PLUGIN_VERSION",
   "identifier_node",
   "tree_list",
   "tree_vec",
   "block",
   "void_type",
   "integer_type",
   "real_type",
   "complex_type",
   "type_argument_pack",
   "nontype_argument_pack",
   "expr_pack_expansion",
   "vector_type",
   "enumeral_type",
   "boolean_type",
   "CharType",
   "nullptr_type",
   "error_mark",
   "type_pack_expansion",
   "pointer_type",
   "offset_type",
   "reference_type",
   "method_type",
   "array_type",
   "set_type",
   "record_type",
   "union_type",
   "qual_union_type",
   "function_type",
   "lang_type",
   "integer_cst",
   "real_cst",
   "complex_cst",
   "vector_cst",
   "void_cst",
   "string_cst",
   "function_decl",
   "label_decl",
   "const_decl",
   "type_decl",
   "using_decl",
   "var_decl",
   "parm_decl",
   "param_packs",
   "result_decl",
   "field_decl",
   "namespace_decl",
   "translation_unit_decl",
   "component_ref",
   "bit_field_ref",
   "indirect_ref",
   "misaligned_indirect_ref",
   "buffer_ref",
   "array_ref",
   "array_range_ref",
   "vtable_ref",
   "constructor",
   "destructor",
   "compound_expr",
   "modify_expr",
   "gimple_assign",
   "init_expr",
   "target_expr",
   "cond_expr",
   "gimple_cond",
   "while_expr",
   "for_expr",
   "gimple_bind",
   "gimple_call",
   "call_expr",
   "aggr_init_expr",
   "gimple_nop",
   "with_cleanup_expr",
   "cleanup_point_expr",
   "placeholder_expr",
   "reduc_max_expr",
   "reduc_min_expr",
   "reduc_plus_expr",
   "plus_expr",
   "ternary_plus_expr",
   "ternary_pm_expr",
   "ternary_mp_expr",
   "ternary_mm_expr",
   "bit_ior_concat_expr",
   "minus_expr",
   "mult_expr",
   "trunc_div_expr",
   "ceil_div_expr",
   "floor_div_expr",
   "round_div_expr",
   "trunc_mod_expr",
   "ceil_mod_expr",
   "floor_mod_expr",
   "round_mod_expr",
   "rdiv_expr",
   "exact_div_expr",
   "fix_trunc_expr",
   "fix_ceil_expr",
   "fix_floor_expr",
   "fix_round_expr",
   "float_expr",
   "lut_expr",
   "negate_expr",
   "min_expr",
   "max_expr",
   "abs_expr",
   "lshift_expr",
   "rshift_expr",
   "lrotate_expr",
   "rrotate_expr",
   "bit_ior_expr",
   "bit_xor_expr",
   "bit_and_expr",
   "bit_not_expr",
   "truth_andif_expr",
   "truth_orif_expr",
   "truth_and_expr",
   "truth_or_expr",
   "truth_xor_expr",
   "truth_not_expr",
   "lt_expr",
   "le_expr",
   "gt_expr",
   "ge_expr",
   "eq_expr",
   "ne_expr",
   "unordered_expr",
   "ordered_expr",
   "unlt_expr",
   "unle_expr",
   "ungt_expr",
   "unge_expr",
   "uneq_expr",
   "ltgt_expr",
   "in_expr",
   "set_le_expr",
   "card_expr",
   "range_expr",
   "paren_expr",
   "convert_expr",
   "nop_expr",
   "non_lvalue_expr",
   "view_convert_expr",
   "save_expr",
   "unsave_expr",
   "addr_expr",
   "reference_expr",
   "fdesc_expr",
   "complex_expr",
   "conj_expr",
   "realpart_expr",
   "imagpart_expr",
   "predecrement_expr",
   "preincrement_expr",
   "postdecrement_expr",
   "postincrement_expr",
   "va_arg_expr",
   "try_catch_expr",
   "try_finally",
   "gimple_label",
   "gimple_goto",
   "goto_subroutine",
   "gimple_return",
   "exit_expr",
   "loop_expr",
   "gimple_switch",
   "gimple_multi_way_if",
   "case_label_expr",
   "gimple_resx",
   "gimple_asm",
   "ssa_name",
   "addr_stmt",
   "def_stmt",
   "use_stmt",
   "gimple_phi",
   "gimple_catch",
   "eh_filter_expr",
   "statement_list",
   "template_decl",
   "template_type_parm",
   "cast_expr",
   "static_cast_expr",
   "typename_type",
   "sizeof_expr",
   "scope_ref",
   "ctor_initializer",
   "do_stmt",
   "expr_stmt",
   "for_stmt",
   "if_stmt",
   "return_stmt",
   "while_stmt",
   "modop_expr",
   "new_expr",
   "vec_cond_expr",
   "vec_perm_expr",
   "dot_prod_expr",
   "vec_lshift_expr",
   "vec_rshift_expr",
   "widen_mult_hi_expr",
   "widen_mult_lo_expr",
   "vec_unpack_hi_expr",
   "vec_unpack_lo_expr",
   "vec_unpack_float_hi_expr",
   "vec_unpack_float_lo_expr",
   "vec_pack_trunc_expr",
   "vec_pack_sat_expr",
   "vec_pack_fix_trunc_expr",
   "vec_extracteven_expr",
   "vec_extractodd_expr",
   "vec_interleavehigh_expr",
   "vec_interleavelow_expr",
   "vec_new_expr",
   "overload",
   "reinterpret_cast_expr",
   "template_id_expr",
   "throw_expr",
   "try_block",
   "arrow_expr",
   "handler",
   "baselink",

   "name",
   "type",
   "srcp",
   "arg",
   "body",
   "strg",
   "lngt",
   "size",
   "algn",
   "retn",
   "prms",
   "scpe",
   "bb_index",
   "used",
   "value",
   "argt",
   "prec",
   "min",
   "max",
   "bit_values",
   "valu",
   "chan",
   "stmt",
   "op",
   "op0",
   "op1",
   "op2",
   "op3",
   "vars",
   "unql",
   "elts",
   "domn",
   "bloc",
   "dcls",
   "mngl",
   "ptd",
   "refd",
   "qual",
   "valr",
   "valx",
   "flds",
   "vfld",
   "bpos",
   "fn",
   "goto",
   "real",
   "imag",
   "bases",
   "binfo",
   "pub",
   "prot",
   "priv",
   "binf",
   "uid",
   "UID",
   "init",
   "fini",
   "purp",
   "pred",
   "succ",
   "phi",
   "res",
   "def",
   "edge",
   "var",
   "vers",
   "orig_vers",
   "cnst",
   "clas",
   "decl",
   "clnp",
   "lab",
   "try",
   "exit",
   "out",
   "in",
   "str",
   "clob",
   "clobber",
   "ref",
   "fncs",
   "csts",
   "rslt",
   "inst",
   "spcs",
   "cls",
   "bfld",
   "ctor",
   "next",
   "cond",
   "expr",
   "then",
   "else",
   "crnt",
   "hdlr",

   "artificial",
   "system",
   "operating_system",
   "library_system",
   "libbambu",
   "extern",
   "C",
   "lshift",
   "global_init",
   "global_fini",
   "undefined",
   "builtin",
   "hwcall",
   "operator",
   "overflow",
   "virt",
   "unsigned",
   "struct",
   "union",
   "constant",
   "readonly",
   "register",
   "static",
   "static_static",
   "reverse_restrict",
   "omp_atomic",
   "omp_body_loop",
   "omp_critical_session",
   "omp_for_wrapper",
   "default",
   "volatile",
   "varargs",
   "Inf",
   "Nan",
   "ENTRY",
   "EXIT",
   "new",
   "delete",
   "assign",
   "member",
   "public",
   "private",
   "protected",
   "noreturn",
   "noinline",
   "always_inline",
   "unused",
   "const",
   "transparent_union",
   "mode",
   "section",
   "aligned",
   "packed",
   "weak",
   "alias",
   "no_instrument_function",
   "malloc",
   "no_stack_limit",
   "no_stack",
   "pure",
   "deprecated",
   "vector_size",
   "visibility",
   "tls_model",
   "nonnull",
   "nothrow",
   "may_alias",
   "warn_unused_result",
   "format",
   "format_arg",
   "NULL",
   "conversion",
   "virtual",
   "mutable",
   "pseudo_tmpl",
   "spec",
   "line",
   "fixd",

   "vecnew",
   "vecdelete",
   "pos",
   "neg",
   "addr",
   "deref",
   "not",
   "lnot",
   "preinc",
   "predec",
   "plusassign",
   "plus",
   "minusassign",
   "minus",
   "multassign",
   "mult",
   "divassign",
   "div",
   "modassign",
   "mod",
   "andassign",
   "and",
   "orassign",
   "or",
   "xorassign",
   "xor",
   "lshiftassign",
   "rshiftassign",
   "rshift",
   "eq",
   "ne",
   "lt",
   "gt",
   "le",
   "ge",
   "land",
   "lor",
   "compound",
   "memref",
   "subs",
   "postinc",
   "postdec",
   "call",
   "thunk",
   "this_adjusting",
   "result_adjusting",
   "ptrmem",
   "r",
   "v",
   "vr",
   "c",
   "cr",
   "cv",
   "cvr",
   "use_tmpl",
   "tmpl_parms",
   "tmpl_args",
   "template_parm_index",
   "index",
   "level",
   "orig_level",
   "inline_body",
   "bitfield",
   "with_size_expr",
   "obj_type_ref",
   "memuse",
   "memdef",
   "vuse",
   "vdef",
   "vover",
   "ptr_info",
   "true_edge",
   "false_edge",
   "pointer_plus_expr",
   "target_mem_ref",
   "target_mem_ref461",
   "mem_ref",
   "widen_sum_expr",
   "widen_mult_expr",
   "mult_highpart_expr",
   "assert_expr",
   "symbol",
   "base",
   "idx",
   "idx2",
   "step",
   "offset",
   "orig",
   "tag",
   "smt_ann",
   "trait_expr",
   "time_weight",
   "size_weight",
   "rtl_size_weight",
   "hpl",
   "loop_id",
   "attributes",
   "pragma_node",
   "pragma_scope",
   "pragma_directive",
   "omp_pragma",
   "omp_critical",
   "omp_declare_simd_pragma",
   "omp_for_pragma",
   "omp_parallel_pragma",
   "omp_parallel_sections_pragma",
   "omp_section_pragma",
   "omp_sections_pragma",
   "omp_shortcut",
   "omp_simd_pragma",
   "omp_target",
   "omp_task",
   "map",
   "call_hw",
   "call_point_hw",
   "hw_component",
   "id_implementation",
   "recursive",
   "issue_pragma",
   "blackbox_pragma",
   "profiling_pragma",
   "statistical_profiling",
   "is_open_pragma",
   "is_block_pragma",
   "pragma_line",
   "empty",
   "gimple_predict",
   "clb",
   "clb_vars",
   "use",
   "use_vars",
   "predicate",
   "slot",

   ///RTL token
   "rtl",

   "abs_R",
   "and_R",
   "ashift_R",
   "ashiftrt_R",
   "bswap_R",
   "call_R",
   "call_insn_R",
   "clz_R",
   "code_label_R",
   "compare_R",
   "concat_R",
   "const_double_R",
   "const_int_R",
   "ctz_R",
   "div_R",
   "eq_R",
   "ffs_R",
   "fix_R",
   "float_R",
   "float_extend_R",
   "float_truncate_R",
   "fract_convert_R",
   "ge_R",
   "geu_R",
   "gt_R",
   "gtu_R",
   "high_R",
   "if_then_else_R",
   "insn_R",
   "ior_R",
   "jump_insn_R",
   "label_ref_R",
   "le_R",
   "leu_R",
   "lshiftrt_R",
   "lt_R",
   "ltgt_R",
   "ltu_R",
   "lo_sum_R",
   "write_mem_R",
   "read_mem_R",
   "minus_R",
   "mod_R",
   "mult_R",
   "ne_R",
   "neg_R",
   "not_R",
   "ordered_R",
   "parallel_R",
   "parity_R",
   "pc_R",
   "plus_R",
   "popcount_R",
   "reg_R",
   "rotate_R",
   "rotatert_R",
   "sat_fract_R",
   "set_R",
   "sign_extend_R",
   "smax_R",
   "smin_R",
   "sqrt_R",
   "symbol_ref_R",
   "truncate_R",
   "udiv_R",
   "umax_R",
   "umin_R",
   "umod_R",
   "uneq_R",
   "unge_R",
   "ungt_R",
   "unle_R",
   "unlt_R",
   "unordered_R",
   "unsigned_fix_R",
   "unsigned_float_R",
   "unsigned_fract_convert_R",
   "unsigned_sat_fract_R",
   "xor_R",
   "zero_extend_R",

   "none_R",
   "qc_R",
   "hc_R",
   "sc_R",
   "dc_R",
   "tc_R",
   "cqi_R",
   "chi_R",
   "csi_R",
   "cdi_R",
   "cti_R",
   "qf_R",
   "hf_R",
   "sf_R",
   "df_R",
   "tf_R",
   "qi_R",
   "hi_R",
   "si_R",
   "di_R",
   "ti_R",
   "v2si_R",
   "v4hi_R",
   "v8qi_R",
   "cc_R",
   "ccfp_R",
   "ccfpe_R",
   "ccz_R",
};

const std::string TI_getTokenName(const TreeVocabularyTokenTypes_TokenEnum i)
{
   const char * tmp = treeVocabularyTokenTypes::tokenNames[static_cast<unsigned int>(i)];
   return std::string(tmp);
}

int treeVocabularyTokenTypes::check_tokens(const char* tok) const
{
   std::map<const char *,int>::const_iterator el = token_map.find(tok);
   if (el == token_map.end())
      return -1;
   else
      return bisontokens[el->second];
}
TreeVocabularyTokenTypes_TokenEnum treeVocabularyTokenTypes::bison2token(int bison) const
{
   std::map<int, TreeVocabularyTokenTypes_TokenEnum>::const_iterator el = from_bisontoken_map.find(bison);
   THROW_ASSERT(el != from_bisontoken_map.end(), "Token " + boost::lexical_cast<std::string>(bison) + " does not exist");
   return el->second;
}
treeVocabularyTokenTypes::treeVocabularyTokenTypes()
{
   for (int i = static_cast<int>(TreeVocabularyTokenTypes_TokenEnum::FIRST_TOKEN) + 1; i < static_cast<int>(TreeVocabularyTokenTypes_TokenEnum::LAST_TOKEN); i++)
   {
      token_map[tokenNames[i]] = i;
      from_bisontoken_map[bisontokens[i]] = static_cast<TreeVocabularyTokenTypes_TokenEnum>(i);
   }
}
