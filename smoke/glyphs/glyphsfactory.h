#ifndef GLYPHSFACTORY_H
#define GLYPHSFACTORY_H


class GlyphsFactory
{
   public:
      enum glyphs
      {
         hedgehog
      };

      ~GlyphsFactory();

      static GlyphsFactory *get()
      {
         static GlyphsFactory instance;

         return &instance;
      }

   private:
      GlyphsFactory();
      GlyphsFactory(const GlyphsFactory&);
      GlyphsFactory& operator =(const GlyphsFactory&) { return *this; }
};

#endif // GLYPHSFACTORY_H
