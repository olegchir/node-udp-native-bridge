{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "node_native_buffer",
      'sources' : [  "<!@(node -p \"require('fs').readdirSync('./src').map(f=>'src/'+f).join(' ')\")" ],
    }
  ]
}
