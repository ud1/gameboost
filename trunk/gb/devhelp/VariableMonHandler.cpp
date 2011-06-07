
#include <math.h>
#include "VariableMonHandler.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 4297)

namespace gb 
{
namespace devhelp 
{

//============================================================
 

	//================================================================
	VariableMonHandler::VariableInfo::VariableInfo(
		const char* name, 
		const VARTYPE::e type, 
		void* address,
		DATA32 mul_fact,
		DATA32 add_factor,
		DATA32 minim,
		DATA32 maxim)   throw()
	{
		m_data32._int = 0;
		m_data_mul_factor._int = 0;
		m_data_add_factor._int = 0;
		m_data_min._int = m_data_max._int = 0; 


		m_data_mul_factor =  mul_fact;
		m_data_add_factor = add_factor;
		m_data_min = minim;
		m_data_max = maxim;


		strncpy(m_name, name, 31 );
		m_type=type;
		m_address=address;

		// select number of items
		switch(m_type)
		{
		case VARTYPE::UDEFINED:
			{
				throw std::runtime_error("undefined type"); 
			}
			break;

		case VARTYPE::BOOL8:
			{
			}
			break;

		case VARTYPE::BOO32:
			{
			}
			break;

		case VARTYPE::INT32:
			{
			}
			break;

		case VARTYPE::UINT32:
			{
			}
			break;

		case VARTYPE::FLOAT:
			{
			}
			break;

		case VARTYPE::FLOAT3_AS_NORMAL:
			{
				//m_numItems=3;
			}
			break;

		case VARTYPE::FLOAT3_AS_COORD:
			{
				//m_numItems=3;
			}
			break;

		case VARTYPE::FLOAT4:
			{
				//			m_numItems=4;
			}
			break;

		case VARTYPE::FLOAT4_AS_COLOR:
			{
				//	m_numItems=4;
			}
			break;






		}

	}


	//===================================================================
	static void __format_float_color(char* buf, float f)
	{
		sprintf(buf, "%1.2f", f);

		int _end =0;
	}
	//
	//===================================================================
	void VariableMonHandler::VariableInfo::_AppendStr(std::string& str, bool bActiveItem) const
	{
		str = "";

		if(bActiveItem)
		{
			str += ">> ";
		}
		else
		{
			str += "   ";
		}

		str += m_name;
		str += " = ";


		char buffer[64];
		buffer[0] = '\0';

		bool* pbool = NULL;
		bool _bool = false;

		long* pbool32 = NULL;
		long _bool32 = 0;

		int* pint = NULL;
		int _int = 0;

		unsigned int* puint = NULL;
		unsigned _uint =0;


		float* pfloat = NULL;
		float _float = 0.0f;

		// add    float array
		//float _float2[2];
		//float _float3[3];
		//float _float4[4];


		switch(m_type)
		{

		case VARTYPE::BOOL8:
			{
				pbool = (bool*)m_address;
				_bool = *pbool;



				if(_bool)
				{
					str += "true";
				}
				else
				{
					str += "false";
				}

			}	  break;

		case VARTYPE::BOO32:
			{
				pbool32 = (long*)m_address;
				_bool32 = *pbool32;

				if(_bool32)
				{
					str += "TRUE";
				}
				else
				{
					str += "FALSE";
				}


			}	  break;   

		case VARTYPE::UINT32:
			{
				puint = (unsigned int*)m_address;
				_uint = *puint;

				sprintf(buffer, "%u", _uint);
				str += buffer;
				//assert(false);


			}	  break;


		case VARTYPE::INT32:
			{
				pint = (int*)m_address;
				_int = *pint;

				sprintf(buffer, "%i", _int);
				str += buffer;
				//assert(false);


			} break;

		case VARTYPE::FLOAT:
			{
				pfloat = (float*)m_address;
				_float = *pfloat;

				sprintf(buffer, "%f", _float);
				str += buffer;

			} break;

		case VARTYPE::FLOAT2:
			{
				assert(false);

				pfloat = (float*)m_address;
				//  _float2[0] = pfloat[0];
				//  _float2[1] = pfloat[1];



				const char* CSTR_FORMAT = "%f";

				// 0
				sprintf(buffer, CSTR_FORMAT, pfloat[0] );
				str += buffer;
				str += "\n";

				// 1
				sprintf(buffer, CSTR_FORMAT, pfloat[1] );
				str += buffer;
				str += "\n";




			} break;


		case VARTYPE::FLOAT3_AS_NORMAL:
			{
				assert(false&&"INSERT CODE");

			} break;

		case VARTYPE::FLOAT3_AS_COORD:
			{

				assert(false&&"INSERT CODE");

			} break;


		case VARTYPE::FLOAT4_AS_COLOR:
			{
				//str += " (COLOR)\n";


				pfloat = (float*)m_address;
				_float = *pfloat;
				__format_float_color(buffer, *pfloat);
				str += buffer;
				//str += "\n";

				// _float4[0] = pfloat[0];
				// _float4[1] = pfloat[1];
				//  _float4[2] = pfloat[2];
				// _float4[3] = pfloat[3];


				/****************
				// formate color
				__format_float_color(buffer, _float4[0] );
				str += "     red   ";
				str += buffer;
				str += "\n";

				__format_float_color(buffer, _float4[1] );
				str += "     green ";
				str += buffer;
				str += "\n";

				__format_float_color(buffer, _float4[2] );
				str += "     blue  ";
				str += buffer;
				str += "\n";

				__format_float_color(buffer, _float4[3] );
				str += "     alpha ";
				str += buffer;
				str += "\n";

				*************************/

				// assert(false);



			}	  break;




		default:
			{
				throw std::runtime_error("unknow variable type");
			}



		}


	}

	static inline bool __compare_float(float f1, float f2, float epsilon)
	{
		if( abs(f1-f2)<=epsilon )
		{
			return true;
		}

		return false;
	}


	//=========================================================================
	void VariableMonHandler::VariableInfo::handle_low_or_hi(bool bLow)
	{

		// эпсилон сравнения с минимальным значеним.
		//	const float C_EPS = 0.001f;
		// домножающий/делящий фактор	для float
		const float C_FLOAT_MUL_FACTOR = m_data_mul_factor._float;
		// увеличивающий/уменьшающий фактор	для float
		const float C_FLOAT_ADD_FACTOR = m_data_add_factor._float;

		// увеличивающий/уменьшающий фактор для int
		//const float C_INT_MUL_FACTOR  = 1.5f;

		bool _bool = false;
		bool* pbool = NULL;

		long* pbool32 = NULL;
		long _bool32 =0;

		float* pfloat = NULL;
		float _float = 0.0f;

		int* pint = NULL;
		int _int =0;

		unsigned int* puint = NULL;
		unsigned int _uint = 0;


		switch(m_type)
		{

		case VARTYPE::BOOL8:
			{
				pbool = (bool*)m_address;
				_bool = *pbool;
				if(_bool)
				{
					*pbool = false;
				}
				else
				{
					*pbool = true;
				}

			}	break;

		case VARTYPE::BOO32:
			{
				pbool32=(long*)m_address;
				_bool32 = *pbool32;

				if(_bool32)
				{
					*pbool32 = 0;
				}
				else
				{
					*pbool32 = 1;
				}

			}	break;


		case VARTYPE::FLOAT:
			{
				pfloat = (float*)m_address;
				_float = *pfloat;

				if(!bLow)
				{
					if(*pfloat<0.0f)
					{
						*pfloat = *pfloat * (1.0f/C_FLOAT_MUL_FACTOR) + C_FLOAT_ADD_FACTOR;
					}
					else
					{
						*pfloat = *pfloat * C_FLOAT_MUL_FACTOR + C_FLOAT_ADD_FACTOR;
					}

				}
				else
				{
					if(*pfloat<0.0f)
					{
						*pfloat = *pfloat * (C_FLOAT_MUL_FACTOR) - C_FLOAT_ADD_FACTOR;
					}
					else
					{
						*pfloat = *pfloat * (1.0f/C_FLOAT_MUL_FACTOR) - C_FLOAT_ADD_FACTOR;
					}


				}
				_float = *pfloat;

				if(_float < m_data_min._float )
				{
					*pfloat = m_data_min._float;
				}

				if(_float>m_data_max._float)
				{
					*pfloat = m_data_max._float;
				}

			}   break;


		case VARTYPE::INT32:
			{
				pint = (int*)m_address;
				_int = *pint;

				if(bLow)
				{
					if(_int<0)
					{
						*pint = *pint - m_data_add_factor._int ;
					}
					else
					{
						*pint = *pint - m_data_add_factor._int;
					}

				}
				else
				{
					if(_int<0)
					{
						*pint = *pint+m_data_add_factor._int;
					}
					else
					{
						*pint = *pint+m_data_add_factor._int;
					}

				}
				_int = *pint;

				if(_int<m_data_min._int)
				{
					*pint =	m_data_min._int;
				}
				if(_int>m_data_max._int)
				{
					*pint =	m_data_max._int;
				}



			}
			break;


		case VARTYPE::UINT32:
			{

				puint = (unsigned int*)m_address;
				_uint = *puint;


				if(bLow)
				{
					if(_uint<0)
					{
						*puint = *puint - m_data_add_factor._uint ;
					}
					else
					{
						*puint = *puint - m_data_add_factor._uint;
					}

				}
				else
				{
					if(_uint<0)
					{
						*puint = *puint + m_data_add_factor._uint;
					}
					else
					{
						*puint = *puint + m_data_add_factor._uint;
					}

				}
				_uint = *puint;

				if(_uint<m_data_min._uint)
				{
					*puint =	m_data_min._uint;
				}
				if(_uint>m_data_max._uint)
				{
					*puint =	m_data_max._uint;
				}


			}	break;

		case VARTYPE::FLOAT4_AS_COLOR:
			{
				pfloat = (float*)m_address;


				if(bLow)
				{
					*pfloat = *pfloat - 0.02f;
				}
				else
				{
					*pfloat = *pfloat + 0.02f;
				}


				if(*pfloat<=0.0f)
				{
					*pfloat = 0.0f;
					break;
				}

			}	break;


		default:
			{
				// default not allowed
				assert(false);
			}

		}

	}

	//==================================================================
	void VariableMonHandler::make_mon_string (std::string& str) const
	{
		str="";
		if(name.length())
		{
			// add name
			str += "(";
			str += name;
			str += ")";
			str += "\n";
		}
		std::string stritem;
		for(size_t c=0; c<m_vector.size(); c++)
		{
			stritem="";
			bool bActiveItem=false;
			if(m_nCurrItem == c)
			{
				bActiveItem=true;
			}

			const VariableInfo& vi = m_vector[c];
			vi._AppendStr(stritem , bActiveItem);

			str += stritem;
			str += "\n";

		}


	}

	//==================================================================
	void VariableMonHandler::handlekey_up()
	{
		if(m_nCurrItem == 0)
		{
			// ставим последний
			m_nCurrItem = m_vector.size()-1;
			return ;
		}

		m_nCurrItem--;	
	}

	//==================================================================
	void VariableMonHandler::handlekey_down()
	{
		// проверка последнего
		if(m_nCurrItem >= m_vector.size()-1)
		{
			m_nCurrItem = 0;
			return ;
		}

		m_nCurrItem++;
	}

	//=========================================================
	void VariableMonHandler::add_bool(const char* name, bool* address)
	{
		VariableInfo::DATA32 d_mul; d_mul._int = 0;
		VariableInfo::DATA32 d_add; d_add._int = 0;
		VariableInfo::DATA32 d_min; d_min._int = 0;
		VariableInfo::DATA32 d_max; d_max._int = 0;

		VariableInfo vi( name, VARTYPE::BOOL8, address,d_mul,d_add, d_min, d_max);
		m_vector.push_back(vi);
	}

	//=========================================================
	void VariableMonHandler::add_bool32(const char* name, long* address)
	{
		VariableInfo::DATA32 d_mul; d_mul._int = 0;
		VariableInfo::DATA32 d_add; d_add._int = 0;
		VariableInfo::DATA32 d_min; d_min._int = 0;
		VariableInfo::DATA32 d_max; d_max._int = 0; 

		VariableInfo vi( name,  VARTYPE::BOO32, address, 
			d_mul,d_add, d_min, d_max);
		m_vector.push_back(vi);

	}     

	//=========================================================
	void VariableMonHandler::add_float(
		const char* name, 
		float* address,
		float mul_factor,
		float add_factor,
		float minimum,
		float maximum
		)
	{
		assert(minimum<maximum);
		VariableInfo::DATA32 d_mul; d_mul._float = mul_factor;
		VariableInfo::DATA32 d_add; d_add._float = add_factor;
		VariableInfo::DATA32 d_min; d_min._float = minimum;
		VariableInfo::DATA32 d_max; d_max._float = maximum;

		VariableInfo vi( name,  VARTYPE::FLOAT, address, 
			d_mul,d_add, d_min, d_max);
		m_vector.push_back(vi);
	}

	//=========================================================
	void VariableMonHandler::add_int(const char* name, 
		int* address, 
		int step,
		int minim,
		int maxim				
		)
	{
		assert(minim<maxim);

		VariableInfo::DATA32 d_mul; d_mul._int = 0;
		VariableInfo::DATA32 d_add; d_add._int = step;
		VariableInfo::DATA32 d_min; d_min._int = minim;
		VariableInfo::DATA32 d_max; d_max._int = maxim;

		VariableInfo vi( name,  VARTYPE::INT32, address, 
			d_mul,d_add, d_min, d_max);
		m_vector.push_back(vi);

	}

	//=========================================================
	void VariableMonHandler::add_uint(const char* name,
		unsigned int* address,
		unsigned int step,
		unsigned int minim, 
		unsigned int maxim)
	{
		assert(minim<maxim);

		VariableInfo::DATA32 d_mul; d_mul._uint = 0;
		VariableInfo::DATA32 d_add; d_add._uint = step;
		VariableInfo::DATA32 d_min; d_min._uint = minim;
		VariableInfo::DATA32 d_max; d_max._uint = maxim;

		VariableInfo vi( name,  VARTYPE::UINT32, address, 
			d_mul,d_add, d_min, d_max);
		m_vector.push_back(vi);

	}




#if (defined(WIN32))
#pragma message("!!!!!! KS777: WINDOWS.H NOT INCLUDED !"  __FILE__)
#endif


#if (defined(WIN32) && defined(_WINDOWS_))

	//=====================================================================
	void VariableMonHandler::msgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

		int nChar = 0; 

		switch(uMsg)
		{

		case WM_KEYDOWN:
			{
				nChar = (int)wParam;

				switch(nChar)
				{

				case VK_UP:
					{
						handlekey_up();
					}
					break;

				case VK_DOWN:
					{
						handlekey_down();
					}
					break;

				case VK_LEFT:
					{
						handlekey_left();
					}
					break;

				case VK_RIGHT:
					{
						handlekey_right();
					}
					break;

				default: {

						 }

				}

			}
			break;


		default:
			{

			}
		}

	};

#endif




//============================================================

}
// end namespace
}
// end namespace

// end file