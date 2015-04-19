# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  # Going with the path of least resistance
  config.vm.box = "ubuntu/trusty32"

  # Virtualbox guests get a shiny GUI because it's a GUI app
  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.name = "leansand vagrant VM"
  end

  # provision the VM with vagrant-bootstrap.sh
  config.vm.provision "shell", :path => "vagrant-bootstrap.sh"
end
