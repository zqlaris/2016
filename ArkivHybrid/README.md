ArkivHybrid API Reference
---
- []()

Usage
---
In order to use this library, include the following file in your html
```html
<script src="arkiv.js" type="text/javascript"></script>
```

Then, you can reference the modules, for example Game, in the following way
```js
Arkiv.Hybrid.Game.startWithPlaceID("XXX", myCallback);
```

Each module also has a "supports" function, that executes asynchronously and checks if the queried function is supported natively in the current platform.
```js
	Arkiv.Hybrid.Game.supports("followUser", function(isSupported) {
		if(isSupported) {
			Arkiv.Hybrid.Game.followUser("XXXXX", myCallback);
		} else {
			// Web implementation
		}
	});
```


How to generate the compiled ArkivHybrid.js file
---
"arkiv.js" is compiled and optimized with [Google Closure Compiler](https://github.com/google/closure-compiler)

In order to run this tool execute:
```sh
$ ./build_js.sh
```

How to generate this documentation
---
```sh
$ cd docs
$ ./build_doc.sh
```
