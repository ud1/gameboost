#include "TextureAtlas.h"

#include <gb/base/nullptr.h>

#include <set>
#include <map>
#include <cassert>

#include <gb/base/Atlas.h>

namespace
{
	using namespace gb::graphics;
	
	template <typename T>
	struct Callback
	{
		T *c;
		bool (T::*f)(int, int);
	};
	
	template <typename T>
	bool resizeFunc(int new_width, int new_height, void *user_data)
	{
		Callback<T> *callback = static_cast<Callback<T>*>(user_data);
		return (callback->c->*(callback->f))(new_width, new_height);
	}
}

namespace gb
{
	namespace graphics2d
	{
		
		using namespace base;
		using namespace containers;
		
		class TextureAtlas::TextureAtlasImpl
		{
		public:
			
			struct ImageBlockImpl : public ImageBlock
			{
				ImageBlockImpl(TextureAtlasImpl *parent) : parent(parent) {}
				
				virtual void destroyThis()
				{
					parent->releaseBlock(this);
				}
				
				TextureAtlasImpl *parent;
			};
			
			TextureAtlasImpl(Device &device) : device(device)
			{
				device.addRef();
				
				resize_callback.c = this;
				resize_callback.f = &TextureAtlasImpl::resizeFunc;
			}
			
			~TextureAtlasImpl()
			{
				assert(blocks.empty());
				device.release();
			}
			
			bool resizeFunc(int new_width, int new_height)
			{
				if (!initialize(new_width, new_height))
					return false;
				
				unused_blocks.clear();
				
				Blocks old_blocks;
				blocks.swap(old_blocks);
				
				for (Blocks::iterator it = old_blocks.begin(); it != old_blocks.end();)
				{
					const ImageBlock *block = createImageBlock(**it, *it);
					assert(block);
				}
				
				return true;
			}
			
			bool initialize(int tex_width, int tex_height)
			{
				atlas = boost::shared_ptr<Atlas>(new Atlas(tex_width, tex_height));
				atlas->setResizeFunc(::resizeFunc<TextureAtlasImpl>, (void *) &resize_callback);
				
				texture = device.createTexture(Texture::Texture2D);
				texture->setMinFilter(Texture::TF_LINEAR);
				texture->setMagFilter(Texture::TF_LINEAR);
				
				Image im;
				im.width = tex_width;
				im.height = tex_height;
				im.pixel_format = ePixelFormat::RGBA_8888;
				im.calculateDataSize();
				
				return texture->setImage(&im, 0);
			}
			
			const ImageBlock *createImageBlock(const containers::Image &image)
			{
				return createImageBlock(image, nullptr);
			}
			
			const ImageBlock *createImageBlock(const containers::Image &image, ImageBlockImpl *old_block)
			{
				Rectangle rec;
				rec.width = image.width;
				rec.height = image.height;
				
				if (getBlock(rec))
				{
					ImageBlockImpl *result;
					if (old_block)
						result = old_block;
					else result = new ImageBlockImpl(this);
					
					*(Rectangle *) result = rec;
					result->copyFrom(image, image.pixel_format);
					texture->setSubImage(&(const Image &) *result, rec.left, rec.top, 0, 0);
					blocks.insert(result);
					return result;
				}
				
				return nullptr;
			}
			
			void releaseBlock(ImageBlockImpl *block)
			{
				blocks.erase(block);
				int id = (block->width << 16) + block->height;
				unused_blocks.insert(std::make_pair(id, *block));
				delete block;
			}
			
			base::RefCntHolder<graphics::Texture> getTexture()
			{
				return texture;
			}
			
		private:
			bool getBlock(Rectangle &rec)
			{
				// Сначала ищем неиспользуемые блоки, чей размер равен в точности требуемому
				int id = (rec.width << 16) + rec.height;
				UnusedBlocks::iterator it = unused_blocks.find(id);
				if (it != unused_blocks.end())
				{
					rec = it->second;
					unused_blocks.erase(it);
					return true;
				}
				
				return atlas->insert(rec);
			}
		
			Device &device;
			base::RefCntHolder<Texture> texture;
			boost::shared_ptr<base::Atlas> atlas;
			typedef std::set<ImageBlockImpl *> Blocks;
			Blocks blocks;
			typedef std::map<int, Rectangle> UnusedBlocks;
			UnusedBlocks unused_blocks;
			
			Callback<TextureAtlasImpl> resize_callback;
		};
		
		TextureAtlas::TextureAtlas(Device& device)
		{
			pimpl = boost::shared_ptr<TextureAtlasImpl>(new TextureAtlasImpl(device));
		}
		
		bool TextureAtlas::initialize(int tex_width, int tex_height)
		{
			return pimpl->initialize(tex_width, tex_height);
		}
		
		const ImageBlock *TextureAtlas::createImageBlock(const containers::Image &image)
		{
			return pimpl->createImageBlock(image);
		}
		
		base::RefCntHolder<Texture> TextureAtlas::getTexture()
		{
			return pimpl->getTexture();
		}
	}
}
