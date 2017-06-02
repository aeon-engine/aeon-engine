/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

using System;
using AeonEngineMono.Assets;
using AeonEngineMono.Gfx;
using AeonEngineMono.Resources;
using AeonEngineMono.Scene;
using AeonEngineMono.Types;

public class MonoApplication
{
    public MonoApplication()
    {
        Console.WriteLine("MonoApplication created.");
    }

    ~MonoApplication()
    {
        Console.WriteLine("MonoApplication destroyed.");
    }

    public void Initialize()
    {
        Console.WriteLine("Initializing game engine!");

        ResourceManager.Mount(new FilesystemCollectionProvider("."), "/");

        _camera = new OrthographicCamera(0, 800, 600, 0);
        _viewport = new Viewport(_camera, "My Viewport");

        SceneNode shipNode = new SceneNode("ShipNode");
        SceneManager.RootSceneNode.AttachChild(shipNode);

        Material material = new Material("/resources/materials/ships.amf");
        Atlas atlas = new Atlas(material, new Vector2F(64, 64));
        AtlasRegion shipRegion = atlas.GetRegionByIndex(10);

        Sprite sprite = new Sprite(shipRegion, 0, "My Ship");
        shipNode.AttachComponent(sprite);
    }

    private OrthographicCamera _camera;
    private Viewport _viewport;

}
