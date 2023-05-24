rec {
  description = "Windstille GUI Engine";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";

    logmich.url = "github:logmich/logmich";
    logmich.inputs.nixpkgs.follows = "nixpkgs";
    logmich.inputs.tinycmmc.follows = "tinycmmc";

    geomcpp.url = "github:grumbel/geomcpp";
    geomcpp.inputs.nixpkgs.follows = "nixpkgs";
    geomcpp.inputs.tinycmmc.follows = "tinycmmc";

    priocpp.url = "github:grumbel/priocpp";
    priocpp.inputs.nixpkgs.follows = "nixpkgs";
    priocpp.inputs.flake-utils.follows = "flake-utils";
    priocpp.inputs.tinycmmc.follows = "tinycmmc";
    priocpp.inputs.logmich.follows = "logmich";
    priocpp.inputs.sexpcpp.follows = "sexpcpp";

    surfcpp.url = "github:grumbel/surfcpp";
    surfcpp.inputs.nixpkgs.follows = "nixpkgs";
    surfcpp.inputs.tinycmmc.follows = "tinycmmc";
    surfcpp.inputs.geomcpp.follows = "geomcpp";
    surfcpp.inputs.logmich.follows = "logmich";

    babyxml.url = "github:grumbel/babyxml";
    babyxml.inputs.nixpkgs.follows = "nixpkgs";
    babyxml.inputs.tinycmmc.follows = "tinycmmc";

    sexpcpp.url = "github:lispparser/sexp-cpp";
    sexpcpp.inputs.nixpkgs.follows = "nixpkgs";
    sexpcpp.inputs.flake-utils.follows = "flake-utils";
    sexpcpp.inputs.tinycmmc.follows = "tinycmmc";

    wstinput.url = "github:windstilleteam/wstinput";
    wstinput.inputs.nixpkgs.follows = "nixpkgs";
    wstinput.inputs.flake-utils.follows = "flake-utils";
    wstinput.inputs.tinycmmc.follows = "tinycmmc";
    wstinput.inputs.logmich.follows = "logmich";
    wstinput.inputs.priocpp.follows = "priocpp";
    wstinput.inputs.sexpcpp.follows = "sexpcpp";

    wstdisplay.url = "github:windstilleteam/wstdisplay";
    wstdisplay.inputs.nixpkgs.follows = "nixpkgs";
    wstdisplay.inputs.tinycmmc.follows = "tinycmmc";
    wstdisplay.inputs.geomcpp.follows = "geomcpp";
    wstdisplay.inputs.babyxml.follows = "babyxml";
    wstdisplay.inputs.surfcpp.follows = "surfcpp";
    wstdisplay.inputs.logmich.follows = "logmich";

    wstsound.url = "github:windstilleteam/wstsound";
    wstsound.inputs.nixpkgs.follows = "nixpkgs";
    wstsound.inputs.flake-utils.follows = "flake-utils";
    wstsound.inputs.tinycmmc.follows = "tinycmmc";
  };

  outputs = { self, nixpkgs, flake-utils,
              tinycmmc, logmich, geomcpp, priocpp, surfcpp, babyxml, sexpcpp,
              wstinput, wstdisplay, wstsound }:

    tinycmmc.lib.eachSystemWithPkgs (pkgs:
      {
        packages = rec {
          default = wstgui;

          wstgui = pkgs.stdenv.mkDerivation {
            pname = "wstgui";
            version = "0.3.0";

            src = nixpkgs.lib.cleanSource ./.;

            cmakeFlags = [ "-DBUILD_EXTRA=ON" ];

            nativeBuildInputs = [
              pkgs.buildPackages.cmake
              pkgs.buildPackages.pkgconfig
            ] ++
            (nixpkgs.lib.optional pkgs.targetPlatform.isLinux pkgs.buildPackages.makeWrapper);

            postFixup =
              (nixpkgs.lib.optionalString pkgs.targetPlatform.isLinux ''
                 wrapProgram $out/bin/wstgui \
                   --prefix LIBGL_DRIVERS_PATH ":" "${pkgs.mesa.drivers}/lib/dri" \
                   --prefix LD_LIBRARY_PATH ":" "${pkgs.mesa.drivers}/lib"
                '') +
              (nixpkgs.lib.optionalString pkgs.targetPlatform.isWindows ''
                mkdir -p $out/bin/
                ln -sfv ${wstdisplay.packages.${pkgs.system}.default}/bin/*.dll $out/bin/

                # FIXME: should be handled by sexpcpp itself
                ln -sfv ${pkgs.jsoncpp}/bin/*.dll $out/bin/
               '');

            buildInputs = [
              babyxml.packages.${pkgs.system}.default
            ];

            propagatedBuildInputs = [
              geomcpp.packages.${pkgs.system}.default
              logmich.packages.${pkgs.system}.default
              priocpp.packages.${pkgs.system}.default
              sexpcpp.packages.${pkgs.system}.default
              surfcpp.packages.${pkgs.system}.default
              tinycmmc.packages.${pkgs.system}.default
              wstdisplay.packages.${pkgs.system}.default
              wstinput.packages.${pkgs.system}.default
              wstsound.packages.${pkgs.system}.default
            ];
           };
        };
      }
    );
}
