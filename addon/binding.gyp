{
  "targets": [
    {
        "include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")"],
        "target_name": "native",
        "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS',"NODE_ADDON_API_ENABLE_MAYBE" ],
        "sources": [ "main.cc" ],
    }
  ]
}